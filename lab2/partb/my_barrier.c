#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

int test_comm(MPI_Comm NewCom)
{

	int nRank;
	int nSize;
	int sNum;

	MPI_Comm_rank(NewCom, &nRank);
	MPI_Comm_size(NewCom, &nSize);

	if (nRank == 0){
		sNum = -1;
		int i;
		int j = 0;
		for ( i = 1; i < nSize; i++){
			MPI_Recv(&sNum, 1, MPI_INT, i, 0, NewCom, MPI_STATUS_IGNORE);
		}
		
		usleep(300);
		for (i = 1; i < nSize; i++){
			MPI_Send(&sNum, 1, MPI_INT, i, 0, NewCom);
		}
	}
	else{
		MPI_Send(&sNum, 1, MPI_INT, 0, 0, NewCom);
		MPI_Recv(&sNum, 1, MPI_INT, 0, 0, NewCom, MPI_STATUS_IGNORE);  			
	}
	
	return nRank;

}
