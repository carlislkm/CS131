#include <string.h>
#include <stdio.h>
#include<stdlib.h>
#include "mpi.h"

int main(int argc, char* argv[])
{


	int num;

	num = MPI_Init(&argc, &argv);
	printf("TEST\n");

	num = MPI_Finalize();



return 0;
}
