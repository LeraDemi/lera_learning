#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

#define LINE_NUM 3
#define LINE_LEN 10

int incr(char* a)
{
	for(int i = 0; i < 37; i++)
	{
		if(a[36 - i] >= '0' && a[36 - i] < '9')
		{
			a[36 - i]++;
			return 0; 
		}
		if(a[36 - i] == '9')
		{
			a[36 - i] = 'A';
			return 0;
		}
		if(a[36 - i] >= 'A' && a[36 - i] < 'Z')
		{
			a[36 - i]++;
			return 0; 
		}
		if(a[36 - i] == 'Z')
		{
			a[36 - i] = 'a';
			return 0;
		}
	    if(a[36 - i] >= 'a' && a[36 - i] < 'z')
		{
			a[36 - i]++;
			return 0; 
		}
		if(a[36 - i] == 'z')
		{
			a[36 - i] = '0';
		}
	}
	return 1;
}


int main(int argc, char* argv[])
{
	
	
	char str[LINE_LEN];
	memset(str,'0', LINE_LEN);
	str[LINE_LEN - 1] = '\n';
	char fileName[20];
	for(int i = 0; i < 2; i++)
	{
		
		snprintf(fileName, sizeof(fileName), "testFiles2/%d.txt", i);
		int fd = open(fileName, O_CREAT | O_WRONLY, S_IRGRP | S_IWUSR | S_IRUSR);
		for(int i = 0; i < LINE_NUM; i++)
		{
#ifdef NOEOL
			if(i == (LINE_NUM - 1))
			{
				str[LINE_LEN -1 ]  = '!';
			}
#endif
			if(!incr(str))
			{
				write(fd, str, LINE_LEN);
			}

		}
		close(fd);
	}	

	
	return 0;
}
/*TODO copy code for incr function and finish task*/
