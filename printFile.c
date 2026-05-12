#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFF_SIZE 0x20
int main(int argc, char* argv[])
{

	int myFile;
	char buff[BUFF_SIZE];
	int rdRes;
	for(int i = 1; i <  argc; i++)
	{
	   myFile = open(argv[i], O_RDONLY);
	   if (myFile < 0)
	   {
		   printf("Error openning file!\n\n");
		   continue;
	   }
	   memset(buff, 0, BUFF_SIZE);
	   while((rdRes = read(myFile, buff, BUFF_SIZE)) > 0)
	   {
	      write(STDOUT_FILENO, buff, rdRes);
       }
       printf("\n");
	   close(myFile);
   }
   return 0;
}
