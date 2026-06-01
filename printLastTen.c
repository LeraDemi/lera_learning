#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define BUFF_SIZE 0x1000
char buff[];


static int countLines()
{
	int i;
	unsigned count = 0;
	for(i = 0; i < BUFF_SIZE; i++)
	{
		if(buff[i] == '\n')
		{
			count++;
		}
	}
	return count;
}

static char* setArrayPtr(unsigned lineCount)
{
	int i;
	char* pBuff;
	for(i = 0; i < BUFF_SIZE; i++)
	{
		if(buff[i] == '\n')
		{
			pBuff = buff + (i + 1);
			lineCount--;
			if(lineCount == 0)
			{
				break;
			}
		}
	}
	return pBuff;
}

static int readIntoBuffer(int fd)
{
	int rdRes = 0;
	int bytesRead = 0;
	do
	{
		if((rdRes = read(fd, buff + rdRes, BUFF_SIZE - bytesRead))>= 0)
		{
			bytesRead += rdRes;
		}
		else 
		{
			perror("Error reading file! ");
			return 0;
		}
   }while(rdRes > 0);
   return 1;
}

int main(int argc, char* argv[])
{
	int myFile;
	myFile = open(argv[1], O_RDONLY);
    
	if (myFile < 0)
	{
		perror("Error openning file! ");
		return EXIT_FAILURE;
	}
	readIntoBuffer(myFile);
    


   return 0;
}


