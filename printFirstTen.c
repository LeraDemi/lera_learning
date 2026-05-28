#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


#define BUFF_SIZE 0x10

char buff[BUFF_SIZE];

static int printLine(void* buff, unsigned size)
{
	int written = 0; 
	int	wrRes;
	while(written < size)
	{
		if((wrRes = write(STDOUT_FILENO, buff + written, size - written)) > 0)
		{
			written += wrRes;
		}
		else
		{
			perror("Error Printing Buffer");
			return 0;
		}
	}
	return 1;
}

static int printTenLines()
{
	int i;
	static int lineCount = 0;
	for(i = 0; i < BUFF_SIZE; i++)
	{
		if(buff[i] == '\n')
		{
			lineCount++;
			if(lineCount == 10)
			{
				printLine(buff, i + 1);
				return 1;
			}
		}
	}
	printLine(buff, BUFF_SIZE);
	return 0;
}

static int readIntoBuffer(int fd)
{
		int rdRes = 0;
		int bytesRead = 0;
		do
		{
			if((rdRes = read(fd, buff + rdRes, BUFF_SIZE - bytesRead))>= 0)
			{
				bytesRead += rdRes;
			}
			else
			{
				perror("Error reading file! ");
				return 0;
			}
	   }while(rdRes > 0);
	   return 1;
}

int main(int argc, char* argv[])
{
	int myFile;
	myFile = open(argv[1], O_RDONLY);
    
	if (myFile < 0)
	{
		perror("Error openning file! ");
		return EXIT_FAILURE;
	}

	while(readIntoBuffer(myFile))
	{
		if(printTenLines())
		{
			break;
		}
	}
	close(myFile);
	return 0;
}

