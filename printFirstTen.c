#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

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

    myFile = open(argv[1], O_RDONLY);
    if (myFile < 0)
    {
	   printf("Error openning file!\n");
	   return myFile;
    }
    for(i = 0; i < 10; i++)
    {
	  printLine(myFile);
    }
    close(myFile);
   
    return 0;
}

