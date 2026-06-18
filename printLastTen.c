#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "common.h"
/**
 * @brief Function counts 10 lines from the end of buffer
 * 
 * This Fuctioin counts 10 \n appearnces in the buffer starting at the end
 * excluding possible \n at the end of buffer.
 * Sets pointer to the begining of the last 10 lines. If less than 10 lines present in buffer 
 * the function will set the pointer to begining of buffer and returns said pointer
 * 
 * @param bytes - Number of bytes in buffer
 * @param buff - Data buffer
 * 
 * @return returns pointer in buffer to begenning of last 10 lines or to begining of buffer if it includes 10 lines or less  
 *  
 * */
static const char* countTenLines(size_t bytes, const void* buff)
{
	size_t i;
	size_t lineCount = 0;
	const char* retPointer;
	const char* pBuff = buff;
	for(i = bytes-2; i >= 0; i--)
	{
		if(pBuff[i] == '\n')
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


int main(int argc, char* argv[])
{
	int myFile;
	ssize_t fileSize;
	const void* pBuff;
	void* buff;
	int readStatus;

	if(argc != 2)
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
	buff = malloc(fileSize);
	if(!buff)
	{
		perror("Error Allocating Buffer!\n");
		return EXIT_FAILURE;
	}

	readStatus = readIntoBuffer(myFile, buff, fileSize);

	if(readStatus < 0)
	{
		return EXIT_FAILURE;
	}
	if(readStatus == 0)
	{
		return EXIT_SUCCESS;
	}
	pBuff = countTenLines(fileSize, buff);

	if(!printBuffer(pBuff, buff + fileSize - pBuff))
	{
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}


