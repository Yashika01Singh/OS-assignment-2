#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>

#define SYS_2d_memcpy 448

int main()
{	
	int row = 2;
	int col = 3;
	int src[2][3] = {{2,3 , 4} , {5,6,7}};
	int dest[row][col];

	printf("Making system call with\n");
	long res = syscall(SYS_2d_memcpy , src , dest , row ,col);
	printf("System call returned %ld, \n" , res);
	return res;
}