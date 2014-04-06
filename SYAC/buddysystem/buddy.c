#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <math.h>

#define FD_STDIN 0 
#define FD_STDOUT 1
#define FD_STDERR 2

void* base_pointer;
int* allocation_heap;
int minimum_size;
int memory_size;

void* allocate(int size) {
	//@TODO
}

void* deallocate(int size) {
	//@TODO
}

int main(int argc, char **argv) {
	int fd_input = FD_STDIN;
	int fd_output = FD_STDOUT; 

	memory_size = 1024*1024;
	minimum_size = 64*1024;
	allocation_heap = malloc(2*(memory_size/minimum_size) - 1);

	// char* buf = malloc(32*sizeof(char));
	// sprintf(buf, "%d", memory_size/minimum_size);
	// write(fd_output, buf, strlen(buf)); 

	base_pointer = malloc(memory_size);

	//@TODO
	

	exit(EXIT_SUCCESS);
	return 0;
}