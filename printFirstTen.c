#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

static ssize_t getFileSize(int fd)
{
	struct stat sStat;
	if(fstat(fd, &sStat))
	{
		perror("Error File Size!");
		return -1;
	}
	return sStat.st_size;
}

static int printLine(const void* buff, size_t size)
{
	size_t written = 0;
	ssize_t	wrRes;
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
				printLine(buff, i + 1);
				return 1;
			}
		}
	}
	printLine(buff, size);
	return 0;
}

static int readIntoBuffer(int fd, const void* buff,  size_t size)
{
		size_t rdRes = 0;
		size_t bytesRead = 0;
		do
		{
			if((rdRes = read(fd, (void*)(buff + rdRes), size - bytesRead))>= 0)
			{
				bytesRead += rdRes;
			}
			else
			{
				perror("Error reading file! ");
				return -1;
			}
	   }
	   while(rdRes > 0);
	   return bytesRead;
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

