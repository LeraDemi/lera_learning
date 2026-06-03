#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define BUFF_SIZE 0x1000
char buff[BUFF_SIZE] = {0};

static int countLines(size_t bytes)
{
	int i;
	size_t lineCount = 0;
	for(i = 0; i < bytes; i++)
	{
		if(buff[i] == '\n')
		{
			lineCount++;
		}
	}

	if(buff[bytes - 1] != '\n')
	{
		lineCount++;
	}
	return lineCount;
}

static char* setArrayPtr(unsigned lineCount)
{
	int i;
	char* pBuff;
	for(i = 0; i < BUFF_SIZE; i++)
	{
		if(buff[i] == '\n')
		{
			pBuff = buff + (i + 1);
			lineCount--;
			if(lineCount == 0)
			{
				break;
			}
		}
	}
	return pBuff;
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
	size_t numOfLines;
	char* pBuff;

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
	numOfLines = countLines(bytes);

	if(numOfLines < 10)
	{
		printBuffer(buff,bytes);
		return EXIT_SUCCESS;
	}
	else
	{
		pBuff = setArrayPtr(numOfLines - 10);
		printBuffer(pBuff,bytes - (pBuff - buff));
	}
	return EXIT_SUCCESS;
}


