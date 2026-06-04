#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

static int getFileSize(int fd)
{
	struct stat sStat;
	if(!fstat(fd, &sStat) == 0)
	{
		perror("Error File Size!");
		return -1;
	}
	return sStat.st_size;
}

static int printLine(void* buff, size_t size)
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

static int printTenLines(void* buff, size_t size, unsigned *lineCount)
{
	int i;
	char* pBuff = (char*)buff;
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

static int readIntoBuffer(int fd, char* buff,  size_t size)
{
		int rdRes = 0;
		int bytesRead = 0;
		do
		{
			if((rdRes = read(fd, buff + rdRes, size - bytesRead))>= 0)
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
	int fileSize;
	int readStatus;
	void* buff;
	unsigned lineCount = 10;

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

