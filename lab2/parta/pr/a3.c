//Kevin Carlisle
//CS 131
//Spring 2015
//Lab 2 
//ACUTAL CODE  
//PART A 
//ATTEMPT 2


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
	int slice_size = 0;
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

		fgets(search_str, sizeof(search_str), fRead);
	        num_threads = atoi(search_str);
	        fgets(search_str, sizeof(search_str), fRead);
	        num_slices = atoi(search_str);
	        fgets(search_str, sizeof(search_str), fRead);
		num_slices = p_size;	
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
		printf("NUM SLICES: %d NUM_INPUTS: %d SIZE: %d\n", num_slices, num_inputs, (num_inputs*sizeof(line)));

	}
	//****ALL RANKS (INCLUDING MASTER)*****
		
	//BCAST VARIABLES TO OTHER PROCESSES
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Bcast(&search_str, 15, MPI_CHAR, 0, MPI_COMM_WORLD);
	MPI_Bcast(&slice_size, 1, MPI_INT, 0, MPI_COMM_WORLD);
			
	char* sub_array;
	sub_array = malloc(slice_size * SIZE);
	memset(sub_array, '\0', slice_size * SIZE);
		
	// Declare POS INT
	int position;

        MPI_Scatter(array_ptr, slice_size*SIZE, MPI_CHAR, sub_array, slice_size*SIZE, MPI_CHAR, 0, MPI_COMM_WORLD);

	position = search_for_string(search_str, sub_array, p_rank, slice_size);
        
	MPI_Gather(&position, 1, MPI_INT, int_array, 1, MPI_INT, 0, MPI_COMM_WORLD);
	// FREE ARRAY 
	//*****END OF ALL RANKS*****

	//**If MASTER PROCESS (MPI_rank == 0)
	if (p_rank == 0)
	{	
			// Stop Timer
			//Write Results to Output file
		//FREE ARRAY
		printf("IN FINAL MASTER\n");
		int i;
		for (i = 0; i < num_slices; i++){
			printf("RESULT --> %d\n", int_array[i]);} 	
	}
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
}

	
	
int search_for_string(char* match_str, char* char_array, int rank_id, int slice_size)
{
	
	int i = 0;
	int found = -1;
	char* temp_ptr = char_array;
	
	while( &temp_ptr[i*SIZE] < &char_array[slice_size * SIZE]){
		if (strcmp( &temp_ptr[i*SIZE], match_str) == 0){
			found = i + (rank_id*slice_size);}
		i++;}
	return found;

}
