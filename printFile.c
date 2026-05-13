#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFF_SIZE 0x20
int main(int argc, char* argv[])
{

	int myFile;
	int rdRes;
	int wrRes;
	int fileSize;
	char* buff;
	for(int i = 1; i <  argc; i++)
	{
	   myFile = open(argv[i], O_RDONLY);
	   
	   if (myFile < 0)
	   {
		   printf("Error openning file!\n\n");
		   continue;
	   }
	   
	   fileSize = lseek(myFile, 0, SEEK_END);
	   
	   lseek(myFile, 0, SEEK_SET);
	   
	   buff = (char*)malloc(sizeof(char	) * fileSize);
	   if(!buff)
	   {
		     printf("Error Allocating Buffer!\n\n");
		     continue;
	   }
	   
	   memset(buff, 0, fileSize);
	   
	   rdRes = read(myFile, buff, fileSize); 

	   if(rdRes < 0)
       {
		   printf("Error While Reading!\n\n");
		   continue;
	   }
	   wrRes = write(STDOUT_FILENO, buff, rdRes);
	   
	   if(wrRes < 0)
	   {
		   printf("Error While Printing!\n\n");
		   continue;
	   }
	   free(buff);
       printf("\n");
	   close(myFile);
   }
   return 0;
}
