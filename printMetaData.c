#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

typedef enum
{
	READ,
	WRITE,
	EXECUTE
}PERMISSIONS;

int main(int argc, char* argv[])
{

	struct stat sStat;
	char owner[4] = { 0 };
	char group[4] = { 0 };
	char other[4] = { 0 };
	if(argc <= 1)
	{
		return EXIT_FAILURE;
	}
	if(stat(argv[1], &sStat))
	{
		perror("Error: ");
		return EXIT_FAILURE;
	}
	owner[READ]    = sStat.st_mode & S_IRUSR ? 'r': '.';
	owner[WRITE]   = sStat.st_mode & S_IWUSR ? 'w': '.';
	owner[EXECUTE] = sStat.st_mode & S_IXUSR ? 'x': '.';

	group[READ]    = sStat.st_mode & S_IRGRP ? 'r': '.';
	group[WRITE]   = sStat.st_mode & S_IWGRP ? 'w': '.';
	group[EXECUTE] = sStat.st_mode & S_IXGRP ? 'x': '.';

	other[READ]    = sStat.st_mode & S_IROTH ? 'r': '.';
	other[WRITE]   = sStat.st_mode & S_IWOTH ? 'w': '.';
	other[EXECUTE] = sStat.st_mode & S_IXOTH ? 'x': '.';

	printf("size = %ld\n",sStat.st_size);
	printf("user id = 0x%x\n", sStat.st_uid);
	printf("group id = 0x%x\n", sStat.st_gid);
	printf("owner permissions = %s\n",owner);
	printf("group permissions = %s\n",group);
	printf("other permissions = %s\n",other);

	return 0;
}
