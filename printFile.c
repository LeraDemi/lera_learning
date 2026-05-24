#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char* argv[])
{
	int myFile;
	int rdRes;
	int wrRes;
	void* buff;
	struct stat sStat;
	unsigned int maxFileSize = 0;

	for(int i = 1; i < argc; i++)
	{
		if(lstat(argv[i], &sStat) == 0)
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
	
	for(int i = 1; i <  argc; i++)
	{
		myFile = open(argv[i], O_RDONLY);
		
		if (myFile < 0)
		{
			perror("Error openning file!");
		    continue;
		}
	   
		while((rdRes = read(myFile, buff, maxFileSize)) > 0)
		{
			int written = 0; 
			while(written < rdRes)
			{
				if((wrRes = write(STDOUT_FILENO, buff + written, rdRes - written)) > 0)
				{
					written += wrRes;
				}
				else
				{
					perror("Error Printing Buffer");
					goto next_file;
				}
			}
		}
		
		if(rdRes < 0)
		{
			perror("Error While Reading");
			goto next_file;
		}
	   
	next_file:
		close(myFile);
	} 
	
	free(buff);
	
	return EXIT_SUCCESS;
}
