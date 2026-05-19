#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>



void goToBeginingOfLine(int fd)
{
	char c = 0;
	while (c != '\n')
	{
		if(!lseek(fd, 0, SEEK_CUR))
		{
			return;
		}
	   lseek(fd, -1, SEEK_CUR);
	   read(fd, &c, 1);
	   lseek(fd, -1, SEEK_CUR);	
	}

}

int main(int argc, char* argv[])
{
   int myFile;
   int i = 0;
   char* buff;
   int fileSize;
   int sizeToPrint = 0;
   int rdRes;
   int wrRes;
   struct stat sStat;

   myFile = open(argv[1], O_RDONLY);
   
   if (myFile < 0)
    {
	   printf("Error openning file!\n");
	   close(myFile);
	   return myFile;
    }
    
    if(fstat(myFile, &sStat) == 0)
    {
	   fileSize = sStat.st_size;
	   printf("fileSize = %d\n",fileSize );
    }
    else
    {
		 printf("Error File Size!\n\n");
		 close(myFile);
		 return -1;
    }
    lseek(myFile, 0, SEEK_END);
   for(i = 0; i < 11; i++)
   {

	   if(lseek(myFile, 0, SEEK_CUR) > 0)
	   {
		   goToBeginingOfLine(myFile);
	   }
	   else
	   {
		   break;
	   }
   }
   
   sizeToPrint = fileSize - lseek(myFile, 0, SEEK_CUR);

   
   /******************************
    * PRINT
    * ****************************/
   
   buff = (char*)malloc(sizeof(char	) * sizeToPrint);
   if(!buff)
   {
		 printf("Error Allocating Buffer!\n\n");
		 close(myFile);
		 return -1;
   }
   
   memset(buff, 0, sizeToPrint);
   
   rdRes = read(myFile, buff, sizeToPrint); 
   if(rdRes < 0)
   {
	   printf("Error While Reading!\n\n");
	   close(myFile);
	   return -1;
	   
   }
   wrRes = write(STDOUT_FILENO, buff, sizeToPrint	);
   
   if(wrRes < 0)
   {
	   printf("Error While Printing!\n\n");
	   close(myFile);
	   return -1;
   }
   free(buff);
   
   close(myFile);
   return 0;
}


