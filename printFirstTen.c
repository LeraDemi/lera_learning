#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


#define BUFF_SIZE 0x100

char buff[BUFF_SIZE];

static int readIntoBuffer(int fd)
{
//	printf("readIntoBuffer\n");
		int rdRes = 0;
		int bytesRead = 0;
		do
		{
			//bytesRead = 0;
			if((rdRes = read(fd, buff + rdRes, BUFF_SIZE - bytesRead))>= 0)
			{
				bytesRead += rdRes;
		//		printf("rdRes = %d\n", rdRes);
	//			printf("bytesRead = %d\n",bytesRead );
				
			}
			else 
			{
				perror("Error reading file! ");
				return 0;
			}
	   }while(rdRes > 0);
//	   printf("bytesRead = %d\n", bytesRead);
//	   printf(" return rdRes = %d\n", rdRes);	
	   return bytesRead;
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
	int lineCount = 0;
    char* pBuff = buff;
    myFile = open(argv[1], O_RDONLY);
    
    if (myFile < 0)
    {
		perror("Error openning file! ");
		return EXIT_FAILURE;
    }
    /*Todo add print buffer when \n is not found*/
    while(readIntoBuffer(myFile))
    {
	//	printf ("%s\n", buff);
		int i;
		pBuff = buff;
		for(i = 0; i < BUFF_SIZE; i++)
		{
		   if(pBuff[i] == '\n')
		   {	
				lineCount++;
				if(lineCount == 10)
				{
					//pBuff+= (i + 1);
					printLine(pBuff, i + 1);
					goto end;
				}
		//		printLine(buff, BUFF_SIZE);
	//			printf("lineCount = %d\n ", lineCount );
				
			}
			
		}
		printLine(buff, BUFF_SIZE); 
		
	}
	end:
	close(myFile);
	return 0;
}

