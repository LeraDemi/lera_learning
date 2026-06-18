#ifndef _COMMON_H
#define _COMMON_H
#include <stdio.h>


ssize_t getFileSize(int fd);
int readIntoBuffer(int fd, void* buff,  size_t size);
int printBuffer(const void* buff, unsigned size);

#endif
