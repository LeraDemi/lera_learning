#include "common.h"
#include <sys/stat.h>
#include <unistd.h>

/**
 * @brief Gets file descriptor and returns its size
 *
 * Function uses fstat to retrieve file size by descriptor
 *
 * @param fd file descriptor
 *
 * @return ssize_t returns the size upon success or -1 if an error accours.
 */
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
/**
 * @brief Function copies bytes from file to a buffer
 *
 * Function calls read command to read bytes from file into the buffer.
 * Fuction checks for errors during file read
 *
 * @param fd File - descriptor
 * @param buff - buffer to copy file content to
 * @param size - size of file in bytes
 *
 * @return returns number of read bytes or 0 if error accurs
 *
 */
int readIntoBuffer(int fd, void* buff,  size_t size)
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
/**
 * @brief This function prints to STDOUT all bytes in buffer
 *
 * This function calls write command to write bytes from buffer to output
 *
 * @param buff - Pionter to buffer to print
 * @param size - Num of bytes to print
 * */
int printBuffer(const void* buff, unsigned size)
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
