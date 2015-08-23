#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

int test(int a)
{

	return (a*2);
}

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
		//for ( i = 1; i < nSize; i++){
		//	printf("MASTER WAITING FOR -> %d\n", i);
		//	fflush(stdout);
			//MPI_Recv(&sNum, 1, MPI_INT, i, 0, NewCom, MPI_STATUS_IGNORE);}
		//	MPI_Recv(&sNum, 1, MPI_INT, MPI_ANY_SOURCE, 0, NewCom, MPI_STATUS_IGNORE);
		//	j++;
		//}
		while ( j < nSize -1)
		{
		//	printf("***************LESS THAN\n");
		//	fflush(stdout);
			MPI_Recv(&sNum, 1, MPI_INT, MPI_ANY_SOURCE, 0, NewCom, MPI_STATUS_IGNORE);
			j++;
		}
		printf("Master RECEIVED ALL\n");
			fflush(stdout);
		for (i = 1; i < nSize; i++){
			MPI_Send(&sNum, 1, MPI_INT, i, 0, NewCom);}
		printf("MASTER DONE \n");
			fflush(stdout);
	}
	else{
		printf("PROCESS [%d] SENDING\n", nRank);
			fflush(stdout);
		MPI_Send(&sNum, 1, MPI_INT, 0, 0, NewCom);
		printf("PROCESS [%d] WAITING\n", nRank);
			fflush(stdout);
		MPI_Recv(&sNum, 1, MPI_INT, 0, 0, NewCom, MPI_STATUS_IGNORE);  			
		printf("PROCESS [%d] DONE\n", nRank);
			fflush(stdout);
	}


	
	return nRank;


}
