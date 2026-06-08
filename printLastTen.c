#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define BUFF_SIZE 0x1000
char buff[BUFF_SIZE] = {0};

static char* countTenLines(size_t bytes)
{
	int i;
	size_t lineCount = 0;
	char* retPointer;
	for(i = bytes-2; i >= 0; i--)
	{
		if(buff[i] == '\n')
		{
			lineCount++;
		}
		if(lineCount == 10)
		{
				break;
		}
	}
	retPointer = buff + i + 1;
	return retPointer;
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
   }
   while(rdRes > 0);
   return bytesRead;
}

static int printBuffer(char* buff, unsigned size)
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
int main(int argc, char* argv[])
{
	int myFile;
	size_t bytes;
	void* pBuff;

	if(argc > 1)
	{
		myFile = open(argv[1], O_RDONLY);
	}
	else
	{
		printf("File Please\n ");
		return EXIT_FAILURE;
	}

	if (myFile < 0)
	{
		perror("Error openning file! ");
		return EXIT_FAILURE;
	}

	bytes = readIntoBuffer(myFile);
	pBuff = countTenLines(bytes);
	printBuffer(pBuff,bytes);
	return EXIT_SUCCESS;
}


