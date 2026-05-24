#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


#define BUFF_SIZE 0x200

void* buff[BUFF_SIZE];



int printLine(int fd)
{
	char c;
	do
	{
		if(read(fd,&c, 0x1))
		{
		   write(STDOUT_FILENO, &c, 0x1);
	    }
	    else return 1;
	}while(c !='\n');
    return 0;
}

int main(int argc, char* argv[])
{

	int myFile;
	int i = 0;
	int rdRes = 0;

    myFile = open(argv[1], O_RDONLY);
    
    if (myFile < 0)
    {
		perror("Error openning file! ");
		return EXIT_FAILURE;
    }
    
    int bytesRead = 0;
    for(i = 0; i < 1; i++)
    {
	  bytesRead = 0;
	 // printLine(myFile);
	  do
      {
		if((rdRes = read(myFile, buff + rdRes, BUFF_SIZE - bytesRead))>= 0)
		{
	     	bytesRead += rdRes;
	    }
	    else 
	    {
			perror("Error reading file! ");
			return EXIT_FAILURE;
		}
		
	   }while(rdRes > 0);
	    
    }
    printf("%s\n", (char*)buff);
    close(myFile);
   
    return 0;
}

