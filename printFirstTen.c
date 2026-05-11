#include <stdio.h>
#include <stdlib.h>
int main(int argv, char* argc[])
{
	char c;
   FILE* myFile;

   myFile = fopen(argc[1], "r");
   if (!myFile)
   {
	   printf("Error openning file!\n");
   }
  for(int i = 0; i < 10; i++)
  {
		while(((c = fgetc(myFile)) != '\n' ) && c != EOF)
		{
		  putchar(c);
		}
		if(c == '\n')putchar(c);
		
  }
   fclose(myFile);
   return 0;
}

