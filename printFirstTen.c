#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


#define BUFF_SIZE 0x200

void* buff[BUFF_SIZE];

static int readIntoBuffer(int fd)
{
		int rdRes = 0;
		int bytesRead;
		do
		{
			bytesRead = 0;
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

int main(int argc, char* argv[])
{

	int myFile;
	int i = 0;
    char* pBuff = (char*)buff;
    myFile = open(argv[1], O_RDONLY);
    
    if (myFile < 0)
    {
		perror("Error openning file! ");
		return EXIT_FAILURE;
    }
    
    for(i = 0; i < 10; i++)
    {
		if(readIntoBuffer(myFile))
		{
			int i;
			int count = 0;
			for(i = 0; i < BUFF_SIZE; i++)
			{
				count++;
				if(pBuff[i] == '\n')
				{
					printLine(pBuff, count);
					pBuff+= count;
					break;
				}
			} 
		}
		else
		{
			goto end;
		}   
    }
    end:
		close(myFile);
		return 0;
}

