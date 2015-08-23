//KEVIN CARLISLE
//CS 131
//LAB 2 
// PROGRAM B
// MY_BARRIER
// MAY 8th, 2015

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include "my_barrier.c"

int my_barrier();


int main(int argc, char** argv)
{

	int pSize;
	int Rank;
	double iTime;
	double eTime;
	FILE* fWrite;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &pSize);
	MPI_Comm_rank(MPI_COMM_WORLD, &Rank);


	if (Rank == 0) {iTime = MPI_Wtime();}
	
	//BARRIER FUNCTION
	my_barrier(MPI_COMM_WORLD);

	if (Rank == 0) {
		eTime = MPI_Wtime();
		fWrite = fopen("out.txt", "w");
		fprintf(fWrite,"RUN TIME = [%f] MS\n", (eTime-iTime)*1000);
		fclose(fWrite);
	}
	
	MPI_Finalize();
	return 0;
}		
int my_barrier()
{

        int nRank;
        int nSize;
        int sNum;
	double rTime = -1;

        MPI_Comm_rank(MPI_COMM_WORLD, &nRank);
        MPI_Comm_size(MPI_COMM_WORLD, &nSize);

        if (nRank == 0){
                sNum = -1;
		double iTime = MPI_Wtime();

                int i;
                for ( i = 1; i < nSize; i++){
                        MPI_Recv(&sNum, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                }
                
                for (i = 1; i < nSize; i++){
                        MPI_Send(&sNum, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
                }	
		double eTime = MPI_Wtime();
		rTime = (eTime - iTime) * 1000;
		//printf("-----------[%f]\n", rTime);
        }
        else{
		sNum = nRank;
                MPI_Send(&sNum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
                MPI_Recv(&sNum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

   	return 0;     

}

