#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

static void printFile(int fd, void* buff, size_t size)
{
	ssize_t rdRes;
	ssize_t wrRes;
	while((rdRes = read(fd, buff, size)) > 0)
	{
		size_t written = 0;
		while(written < rdRes)
		{
			if((wrRes = write(STDOUT_FILENO, buff + written, rdRes - written)) > 0)
			{
				written += wrRes;
			}
			else
			{
				perror("Error Printing Buffer");
				return;
			}
		}
	}

	if(rdRes < 0)
	{
		perror("Error While Reading");
	}
}

int main(int argc, char* argv[])
{
	int myFile;
	void* buff;
	struct stat sStat;
	size_t maxFileSize = 0;
    int fileIndx;
    
	for(fileIndx = 1; fileIndx < argc; fileIndx++)
	{
		if(stat(argv[fileIndx], &sStat) == 0)
		{
			if(sStat.st_size > maxFileSize )
			{
				maxFileSize = sStat.st_size;
			}
		}
		else
		{
			perror("Error File Size!");
			continue;		   
		}
	  }
	
	buff = malloc(maxFileSize);
		   
	if(!buff)
	{
		perror("Error Allocating Buffer!");
		return EXIT_FAILURE;
	}
	
	for(fileIndx = 1; fileIndx < argc; fileIndx++)
	{
		myFile = open(argv[fileIndx], O_RDONLY);
		
		if (myFile < 0)
		{
			perror("Error openning file!");
		    continue;
		}

		printFile(myFile, buff, maxFileSize);

		close(myFile);
	} 
	
	free(buff);
	
	return EXIT_SUCCESS;
}
