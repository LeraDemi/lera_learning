#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>


/**
 * @brief Gets file descriptor and returns its size
 *
 * Function uses fstat to retrieve file size by descriptor
 *
 * @param fd file descriptor
 * 
 * @return ssize_t returns the size upon success or -1 if an error accours.
 */
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
static char* countTenLines(size_t bytes, void* buff)
{
	int i;
	size_t lineCount = 0;
	char* retPointer;
	char* pBuff = buff;
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
static int readIntoBuffer(int fd, void* buff, size_t size)
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
			return 0;
		}
   }
   while(rdRes > 0);
   return bytesRead;
}
/**
 * @brief This function prints to STDOUT all bytes in buffer
 * 
 * This fuction calls write command to write bytes from buffer to output
 * 
 * @param buff - Pionter to buffer to print
 * @param size - Num of bytes to print
 * */
static int printBuffer(char* buff, unsigned size)
{
	size_t written = 0;
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
	ssize_t fileSize;
	void* pBuff;
	void* buff;

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
	buff = malloc(fileSize);
	if(!buff)
	{
		perror("Error Allocating Buffer!\n");
		return EXIT_FAILURE;
	}
	if(!readIntoBuffer(myFile, buff, fileSize))
	{
		return EXIT_FAILURE;
		
	}
	pBuff = countTenLines(fileSize, buff);

	if(!printBuffer(pBuff,fileSize))
	{
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}


