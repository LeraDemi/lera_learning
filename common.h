#ifndef _COMMON_H
#define _COMMON_H
#include <stdio.h>

/**
 * @brief Gets file descriptor and returns its size
 *
 * Function uses fstat to retrieve file size by descriptor
 *
 * @param fd file descriptor
 *
 * @return ssize_t returns the size upon success or -1 if an error accours.
 */
ssize_t getFileSize(int fd);
/**
 * @brief Function copies bytes from file to a buffer
 *
 * Function calls read command to read bytes from file into the buffer.
 * Fuction checks for errors during file read
 *
 * @param fd File - descriptor
 * @param buff - buffer to copy file content to
 * @param size - size of file in bytes
 *
 * @return returns number of read bytes or 0 if error accurs
 *
 */
int readIntoBuffer(int fd, void* buff, size_t size);
}
/**
 * @brief This function prints to STDOUT all bytes in buffer
 *
 * This function calls write command to write bytes from buffer to output
 *
 * @param buff - Pionter to buffer to print
 * @param size - Num of bytes to print
 * */
int printBuffer(const void* buff, size_t size);

#endif
