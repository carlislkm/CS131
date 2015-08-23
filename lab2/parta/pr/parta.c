//Kevin Carlisle
//CS 131
//Spring 2015
//Lab 2 
//ACUTAL CODE  
//PART A 
//ATTEMPT 1

//Write an MPI program to search an array of strings for a given pattern. 
//Each MPI task works on a seperate slice of the array. Produce the 
//location of the string in the array.
//The input file defines the number of tasks (NT) in the first line, 
//the number of slices (NS) in the second line, the search string in 
//the third line. The remaining 100k lines in the input file contain 
//strings (up to 15 char in length).
//A master task reads 3 parameters into variables and the string file
//into the seach array declared in your program.
//The master task (mpi_rank = 0) distributes the array in slices to all tasks
//(slice i to task i) (NT = NS). Use MPI_Scatter() to do this.
//Each task checks for the exact match with the search string in its slice 
//and sends the answer back to the master. 
//After all tasks complete execution, the master task writes the results
//of each thread to an output file, followed by the total execution time
//(in milliseconds) of the program. Use MPI_W time for timing. 

//DEFINE SIZE -> SIZE OF STRING LINE
#define SIZE 15

#include <string.h>             //String Handling
#include <stdlib.h>             //General Utilities
#include <stdio.h>              //Input / Output        
#include <fcntl.h>
#include <unistd.h>             //Symbolic Constants
#include <sys/types.h>          //Primitive System Data Types
#include <errno.h>              //ERRORS
#include <pthread.h>            //POSIX THREADS
#include <mpi.h> 

//SEARCH FUNCTION
int search_for_string(char* match_str, char* char_array, int p_rank, int slice_size);

//Main
int main(int argc, char** argv)
{
	//Initialize MPI
	MPI_Init(NULL, NULL);
	
	//Declare/Initialize --> MPI_size int
	int p_size;
	MPI_Comm_size(MPI_COMM_WORLD, &p_size);

	//Declare/Initialize --> MPI_rank int
	int p_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &p_rank);
	
	//RESULT ARRAY
	int int_array[p_size];

	//Declare/Initialize --> MPI_Wtime 
	
//	if ( argc > 2)
//	{
		//ARGV[1] = INPUT FILE
//		char* input_file = argv[1];
		//ARGV[2] = OUTPUT FILE
//		char* output_file = argv[2];
//	}
//	else{exit(1);}
	

	//VARIABLE DECLARATIONS---------------------------------------------------------
	int slice_size =25000;
	char* array_ptr = NULL;
	FILE* fRead;
	char temp_file[] = "fartico_aniketsh_input_partA.txt";
	int num_inputs = 0;
	int fchar;
	char search_str[SIZE];
	int num_threads;
	int num_slices;
	char line[SIZE];
	int i = 0;
	char* temp_ptr;

	//END VARIABLE DECLARATIONS------------------------------------------------------
	//If MASTER PROCESS (MPI_rank == 0)
	if ( p_rank == 0)
	{
		// Start Timer
		// OPEN FILE
		fRead = fopen(temp_file, "r");
		// ENSURE FILE OPEN
		if( fRead == NULL){perror("FILE OPEN FAILED\n");
				exit(1);}
		

		// READ REMAINING LINES IN FILE AND STORE COUNT
			//INTO VARIABLE (INT) --> NUM_INPUTS
		while(EOF != (fchar = fgetc(fRead)))
                	{if ( fchar == '\n'){++num_inputs;}}
        	if ( fchar != '\n' ){++num_inputs;}
		if (num_inputs > 4) {num_inputs = num_inputs -3;}
		// CLOSE FILE
        	fclose(fRead);

		// REOPEN FILE, ENSURE OPEN
		fRead = fopen(temp_file, "r");
		// ENSURE FILE OPEN
		if( fRead == NULL){perror("FILE OPEN FAILED\n");
				exit(1);}
		// READ FIRST THREE LINES (NT, NS, SEARCH_STR) 
			// INTO VARIABLES (INT, INT, CHAR*)

		fgets(search_str, sizeof(search_str), fRead);
	        num_threads = atoi(search_str);
	        fgets(search_str, sizeof(search_str), fRead);
	        num_slices = atoi(search_str);
	        fgets(search_str, sizeof(search_str), fRead);
		
		// Declare array to store input file
			// SIZE (NUM_INPUTS * SIZE OF LINE( 15 chars ))	
		array_ptr = malloc(num_inputs * sizeof(line));
		memset(array_ptr, '\0', num_inputs * sizeof(line));
		temp_ptr = array_ptr;

		//STRCPY INTO ARRAY
		while( fgets(line, sizeof(line), fRead))
		{
			strcpy(&temp_ptr[i*SIZE], line);
			i++;
		}	
		//Set Size of Slices
		slice_size =  num_inputs / num_slices;
		printf("FIRST STRING: %s\n", array_ptr);
		printf("NUM SLICES: %d NUM_INPUTS: %d SIZE: %d\n", num_slices, num_inputs, (num_inputs*sizeof(line)));

	}
	// END IF 
	//if (p_rank != 0){ int int_array[5];}	
	
	//****ALL RANKS (INCLUDING MASTER)*****
		// Declare buffer array to hold subset of the array
			//SIZE (SIZE OF SLICE * SIZE OF LINE ( 15 chars ))
		
		//BCAST VARIABLES TO OTHER PROCESSES
		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Bcast(&search_str, 15, MPI_CHAR, 0, MPI_COMM_WORLD);
			
		char* sub_array;
		sub_array = malloc(slice_size * SIZE);
		memset(sub_array, '\0', slice_size * SIZE);
		
		// Declare POS INT
		int position;

		// MPI_Scatter() --> &ARRAY, MASTER_ID, SIZE OF SLICE, NUM SLICE
			// Scatter Array by SIZE of SLICE 
			// int MPI_Scatter(const void *sendbuf, int (SIZE_SLICE), 
				//MPI_Datatype char,
               //void *recvbuf, int NS, MPI_Datatype int, int 0,
               //MPI_Comm MPI_COMM_WORLD)
              // printf("------PRE-------SLICE_SIZE: %d SUB_ARRAY: %s\n", slice_size, *sub_array);
               MPI_Scatter(array_ptr, slice_size*SIZE, MPI_CHAR, sub_array, slice_size*SIZE, MPI_CHAR, 0, MPI_COMM_WORLD);

               //printf("-----POST-------SLICE_SIZE: %d SUB_ARRAY: %s\n", slice_size, *sub_array);
		// CALL SEARCH FUNCTION
			// RETURN INT POS FOUND OR -1 IF NOT FOUND
		//position = -1;
		position = search_for_string(search_str, sub_array, p_rank, slice_size);
		// MPI_Gather() --> &POS, (RECV_BUFFER[NUM_INTS])
			// Return pos int from each process to array of INTS
			// in MASTER
			// int MPI_Gather(const void *sendbuf, int (NS), 
				//MPI_Datatype int,
               //void *recvbuf, int SIZE_SLICE, MPI_Datatype char, int rank,
               //MPI_Comm MPI_COMM_WORLD)
               MPI_Gather(&position, 1, MPI_INT, int_array, 1, MPI_INT, 0, MPI_COMM_WORLD);
		// FREE ARRAY 
	//*****END OF ALL RANKS*****
		// SIZE [NUM SLICES] 

	//**If MASTER PROCESS (MPI_rank == 0)
	if (p_rank == 0)
	{	
		// CALL WRITE TO FILE FUNCTION WITH RECV_BUFFER
			// USE POS IN ARRAY TO DETERMINE SLICE
			// USE POS IN ARRAY TO DETERMINE ABSOLUTE POS
			// Stop Timer
			//Write Results to Output file
		//FREE ARRAY
		printf("IN FINAL MASTER\n");
		int i;
		for (i = 0; i < 4; i++)
		{
			printf("RESULT --> %d\n", int_array[i]);
		} 	
	}
	//MPI_Finalize()
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
}

	
	
int search_for_string(char* match_str, char* char_array, int rank_id, int slice_size)
{
	//printf("STR_LEN: %d\n", strlen(match_str));	
	//char* temp;
	//temp = match_str;
//	while(*temp)
//	{
//		if(*temp == '\n')
//		{
//			*temp = '\0';
//		}
//		temp++;
//	}
	
	int i = 0;
	int found = -1;
	//printf("FIRST-->%d -%s-\n",slice_size, char_array);	
	
	//printf("LAST---> -%s-\n", &char_array[(slice_size-1) * SIZE]);	
	char* temp_ptr = char_array;
	//printf("LAST---> -%s-\n", &char_array[slice_size]);	
	while( &temp_ptr[i*SIZE] < &char_array[slice_size * SIZE])
	{
		//printf("------%s", &temp_ptr[i*SIZE]);
		if (strcmp( &temp_ptr[i*SIZE], match_str) == 0)
		{
			found = i + (rank_id*slice_size);
	//		printf("Rank :%d ", rank_id);

		}
		i++;

	}

	//printf("I: %d\n", i);
	return found;

}
