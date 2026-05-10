#include <stdio.h>
#include <stdlib.h>
int main(int argv, char* argc[])
{
	char c;
	for(int i = 1; i <  argv; i++){
	   myFile = fopen(argc[i], "r");
	   if (!myFile)
	   {
		   printf("Error openning file!\n");
	   }
	   while((c = fgetc(myFile)) != EOF )
	   {
	      putchar(c);
       }
	   fclose(myFile);
   }
   return 0;
}
