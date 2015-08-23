#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  	
    const int PING_PONG_LIMIT = 10;

  	// Initialize the MPI environment
  	MPI_Init(NULL, NULL);
  	
	// Find out rank, size
  	int world_rank;
  	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  	int world_size;
  	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  
  	// We are assuming at least 2 processes for this task
  	if (world_size != 2) {
  		fprintf(stderr, "World size must be two for %s\n", argv[0]);
  		MPI_Abort(MPI_COMM_WORLD, 1); 
                             }
  
  	int ping_pong_count = 0;
  	int partner_rank = (world_rank + 1) % 2;
	printf("---Process(%d) Partner Rank(%d) World Size(%d)\n\n", world_rank, partner_rank, world_size);
  	while (ping_pong_count < PING_PONG_LIMIT)
	 {
     		if (world_rank == ping_pong_count % 2) 
		{
       			// Increment the ping pong count before you send it
       			ping_pong_count++;
       			MPI_Send(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
       			printf("------SEND COUNT (%d) FROM (%d) TO (%d)\n",
                        ping_pong_count,world_rank, partner_rank);
			fflush(stdout);
    		} 
		else
		{
         		MPI_Recv(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD,                                                                              MPI_STATUS_IGNORE);
 	 		printf("           RECEIVED COUNT (%d) FROM ( %d) (%d)\n\n",                                                               ping_pong_count, partner_rank, world_rank);
       		 } 	fflush(stdout);
          	                                                                                           }
    MPI_Finalize();
                                                                                                      }
