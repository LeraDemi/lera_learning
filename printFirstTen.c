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

static int printTenLines(char* buff, size_t size)
{
	int i;
	static int lineCount = 0;
	for(i = 0; i < size; i++)
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
	   }while(rdRes > 0);
	   return bytesRead;
}

int main(int argc, char* argv[])
{
	int myFile;
	int fileSize;
	char* buff;

	myFile = open(argv[1], O_RDONLY);
    
	if (myFile < 0)
	{
		perror("Error openning file! ");
		return EXIT_FAILURE;
	}
	if((fileSize = getFileSize(myFile) )> 0)
	{
		buff = (char*)malloc(fileSize);
		if(!buff)
		{
			perror("Error Allocating Buffer!\n");
			return EXIT_FAILURE;
		}
	}
	else if(fileSize < 0)
	{
		return EXIT_FAILURE;
	}
	else
	{
		return EXIT_SUCCESS;
	}
	while(readIntoBuffer(myFile, buff, fileSize))
	{
		if(!printTenLines(buff, fileSize))
		{
			break;
		}
	}
	close(myFile);
	return EXIT_SUCCESS;
}

