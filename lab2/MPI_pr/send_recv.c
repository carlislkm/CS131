#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	
	// Initialize the MPI environment
  	MPI_Init(NULL, NULL);
  	
	// Find out rank, size
  	int world_rank;
  	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  	
	int world_size;
  	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	printf("-----START PROCESS (RANK -> %d )\n", world_rank);
 
  	// We are assuming at least 2 processes for this task
  	if (world_size < 2) 
	{
        	fprintf(stderr, "World size must be greater than 1 for %s\n", argv[0]);
                          MPI_Abort(MPI_COMM_WORLD, 1); 
        }
  
  	int number;
  	if (world_rank == 0) 
	{
		printf("-----ABOUT TO SEND (RANK -> %d )\n", world_rank);
         	
		// If we are rank 0, set the number to -1 and send it to process 1
         	number = -1;
         	
		MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		
		printf("-----MESSAGE SENT (RANK -> %d )\n", world_rank);
        }
   	else if (world_rank == 1)
	{
		printf("-----WAITING TO RECEIVE (RANK -> %d )\n", world_rank);
        	
		MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                
		printf("Process 1 received number %d from process 0\n", number);
		printf("-----MESSAGE RECEIVED (RANK -> %d )\n", world_rank);
        }
	printf("-----END OF PROGRAM ( %d )\n", world_rank);
    	MPI_Finalize();
}


/*
int MPI_Send(void *data_to_send, int send_count, MPI_Datatype send_type, 
      int destination_ID, int tag, MPI_Comm comm); 
data_to_send: variable of a C type that corresponds to the send_type supplied below
send_count: number of data elements to be sent (nonnegative int)
send_type: datatype of the data to be sent (one of the MPI datatype handles)
destination_ID: process ID of destination (int)
tag: message tag (int)
comm: communicator (handle)

int MPI_Recv(void *received_data, int receive_count, MPI_Datatype receive_type, 
      int sender_ID, int tag, MPI_Comm comm, MPI_Status *status); 
received_data: variable of a C type that corresponds to the receive_type supplied below
receive_count: number of data elements expected (int)
receive_type: datatype of the data to be received (one of the MPI datatype handles)
sender_ID: process ID of the sending process (int)
tag: message tag (int)
comm: communicator (handle)
status: status struct (MPI_Status)

*/