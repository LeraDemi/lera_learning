#include "common.h"
#include <sys/stat.h>
#include <unistd.h>

ssize_t getFileSize(int fd)
{
	struct stat sStat;
	if(fstat(fd, &sStat))
	{
		perror("Error File Size!");
		return -1;
	}
	return sStat.st_size;
}

int readIntoBuffer(int fd, void* buff, size_t size)
{
	ssize_t rdRes = 0;
	size_t bytesRead = 0;
	do
	{
		if((rdRes = read(fd, buff + bytesRead, size - bytesRead))>= 0)
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

int printBuffer(const void* buff, size_t size)
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
