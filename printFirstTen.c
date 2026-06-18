#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "common.h"

static int printTenLines(const void* buff, size_t size, ssize_t *lineCount)
{
	int i;
	const char* pBuff = buff;
	for(i = 0; i < size; i++)
	{
		if(pBuff[i] == '\n')
		{
			(*lineCount)--;
			if(*lineCount == 0)
			{
				printBuffer(buff, i + 1);
				return 1;
			}
		}
	}
	printBuffer(buff, size);
	return 0;
}

int main(int argc, char* argv[])
{
	int myFile;
	ssize_t fileSize;
	int readStatus;
	void* buff;
	ssize_t lineCount = 10;

	if(argc <= 1)
	{
		printf("File Please\n ");
		return EXIT_FAILURE;
	}

	myFile = open(argv[1], O_RDONLY);
	if (myFile < 0)
	{
		perror("Error openning file! ");
		return EXIT_FAILURE;
	}

	fileSize = getFileSize(myFile);

	if(fileSize < 0)
	{
		return EXIT_FAILURE;
	}
	if(fileSize == 0)
	{
		return EXIT_SUCCESS;
	}

	buff = malloc(fileSize);
	if(!buff)
	{
		perror("Error Allocating Buffer!\n");
		return EXIT_FAILURE;
	}

	if((readStatus = readIntoBuffer(myFile, buff, fileSize)) > 0)
	{
		while(lineCount > 0)
		{
			if(!printTenLines(buff, fileSize, &lineCount))
			{
				break;
			}
		}
	}

	if(readStatus < 0)
	{
		return EXIT_FAILURE;
	}
	close(myFile);
	return EXIT_SUCCESS;
}

