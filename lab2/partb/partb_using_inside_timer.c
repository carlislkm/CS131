#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include "my_barrier.c"

double my_barrier(MPI_Comm NewCom);


int main(int argc, char** argv)
{

	int pSize;
	int Rank;
	double runTime = -1;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &pSize);
	MPI_Comm_rank(MPI_COMM_WORLD, &Rank);


	printf("[%d] BEFORE\n", Rank);
	fflush(stdout);
	
	//BARRIER FUNCTION
	runTime = my_barrier(MPI_COMM_WORLD);


	printf("---- [%d][%f] DONE\n", Rank, runTime);
	fflush(stdout);
	
	
	MPI_Finalize();
}		
double my_barrier(MPI_Comm NewCom)
{

        int nRank;
        int nSize;
        int sNum;
	double rTime = -1;

        MPI_Comm_rank(NewCom, &nRank);
        MPI_Comm_size(NewCom, &nSize);

        if (nRank == 0){
                sNum = -1;
		double iTime = MPI_Wtime();

                int i;
                for ( i = 1; i < nSize; i++){
                        MPI_Recv(&sNum, 1, MPI_INT, i, 0, NewCom, MPI_STATUS_IGNORE);
                }
                
                for (i = 1; i < nSize; i++){
                        MPI_Send(&sNum, 1, MPI_INT, i, 0, NewCom);
                }	
		double eTime = MPI_Wtime();
		rTime = (eTime - iTime) * 1000;
        }
        else{
		sNum = nRank;
                MPI_Send(&sNum, 1, MPI_INT, 0, 0, NewCom);
                MPI_Recv(&sNum, 1, MPI_INT, 0, 0, NewCom, MPI_STATUS_IGNORE);
        }

        return rTime;

}

