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

	//Declare/Initialize --> MPI_Wtime 
	
//	if ( argc > 2)
//	{
		//ARGV[1] = INPUT FILE
//		char* input_file = argv[1];
		//ARGV[2] = OUTPUT FILE
//		char* output_file = argv[2];
//	}
//	else{exit(1);}

	int slice_size =25000;
	char* array_ptr = NULL;

	//If MASTER PROCESS (MPI_rank == 0)
	if ( p_rank == 0)
	{
		//VARIABLE DECLARATIONS
		FILE* fRead;
		char temp_file[] = "fartico_aniketsh_input_partA.txt";
		int num_inputs = 0;
		int fchar;
		char search_str[SIZE];
		int num_threads;
		int num_slices;
		char line[SIZE];

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
		
		//Set Size of Slices
		slice_size =  num_inputs / num_slices;

	}
	// END IF 
	MPI_Barrier(MPI_COMM_WORLD);
	printf("TESTING %d\n", p_rank);		
	MPI_Finalize();
}

	
	
