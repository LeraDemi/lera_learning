#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define BUFF_SIZE 0x20
int main(int argc, char* argv[])
{

	int myFile;
	int rdRes;
	int wrRes;
	int fileSize;
	char* buff;
	struct stat sStat;
	for(int i = 1; i <  argc; i++)
	{
	   myFile = open(argv[i], O_RDONLY);
	   
	   if (myFile < 0)
	   {
		   printf("Error openning file!\n\n");
		   close(myFile); 
		   free(buff);
		   continue;
	   }
	   
	   if(fstat(myFile, &sStat) == 0)
	   {
		   fileSize = sStat.st_size;
	   }
	   else
	   {
		     printf("Error File Size!\n\n");
		     close(myFile);
		     free(buff);
		     continue;		   
	   }
	   
	   buff = (char*)malloc(sizeof(char	) * fileSize);
	   if(!buff)
	   {
		     printf("Error Allocating Buffer!\n\n");
		     close(myFile);
		     free(buff);
		     continue;
	   }
	   
	   memset(buff, 0, fileSize);
	   
       while((rdRes = read(myFile, buff, BUFF_SIZE)) > 0)
	   {
	      write(STDOUT_FILENO, buff, rdRes);
       }
	   if(rdRes < 0)
       {
		   printf("Error While Reading!\n\n");
		   close(myFile);
		   free(buff);
		   continue;
	   }
	   wrRes = write(STDOUT_FILENO, buff, rdRes);
	   
	   if(wrRes < 0)
	   {
		   printf("Error While Printing!\n\n");
		   free(buff);
		   close(myFile);
		   continue;
	   }
	   free(buff);
       printf("\n");
	   close(myFile);
   }
   return 0;
}
