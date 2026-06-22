#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "common.h"

/**
 * @brief Function looks for string in a line and prints it if found
 *
 * This functon recieves one line and prints it if string is found within the line
 *
 * @param - str String to find
 * @param - buff Buffer to search in and print
 * @param - size of buffer
 *
 * @return - void
 *
 */
static void findStringInLine(const char* str, char* buff, size_t size)
{
	size_t i = 0;
    size_t strSize = strlen(str);

	if(size < strSize)
	{
		return;
	}
	while (i < size - (strSize - 1))
	{
		if(!memcmp(&buff[i], str, strSize))
		{
			printBuffer(buff, size);
			return;
		}
		i++;
	}
}
/**
 * @brief Function looks for string in a buffer and prints all lines in which it appears
 *
 *
 * @param - buff Buffer to search in and print
 * @param - size of buffer
 * @param - str String to find
 *
 * @return - void
 *
 */
static void search(char* buff, size_t size, const char* str)
{
	size_t count = 0;
	size_t i = 0;
	char* pBuff = buff;
	char* curr_line = buff;
	while(i < size - 1)
	{
		if(pBuff[i] == '\n')
		{
			findStringInLine(str, curr_line, count + 1);
			curr_line+= count + 1;
			count = 0;
		}
		else
		{
			count++;
		}
		i++;
	}

	if(count > 0)
	{
		findStringInLine(str, curr_line, count + 1);
	}
}
int main(int argc, char* argv[])
{
	int myFile;
	ssize_t fileSize;
	int readStatus;
	void* buff;
	char* string;

	if(argc < 3)
	{
		printf("File and string please\n ");
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

	string = argv[2];

	buff = malloc(fileSize);
	if(!buff)
	{
		perror("Error Allocating Buffer!\n");
		close(myFile);
		return EXIT_FAILURE;
	}

	readStatus = readIntoBuffer(myFile, buff, fileSize);

	if(readStatus < 0)
	{
		free(buff);
		close(myFile);
		return EXIT_FAILURE;
	}
	if(readStatus == 0)
	{
		free(buff);
		close(myFile);
		return EXIT_SUCCESS;
	}

	search(buff, fileSize, string);

	close(myFile);
	return EXIT_SUCCESS;
}
