#include <string.h>		//String Handling
#include <stdlib.h>		//General Utilities
#include <stdio.h>		//Input / Output	
#include <fcntl.h>
#include <unistd.h>		//Symbolic Constants
#include "Timer.h"		//Timer
#include <sys/types.h>          //Primitive System Data Types
#include <errno.h>		//ERRORS
#include <pthread.h>		//POSIX THREADS

//PROTOTYPE FOR THREAD ROUTINE
void search_by_thread( void* ptr);

//STRUCT TO STORE DATA TO PASS TO THREAD FUNCTION
typedef struct thread_struct
{
	char* start_ptr;
	char* end_ptr;
	int num;
	char match_str[16];

} thread_data;

pthread_mutex_t mutex;


//MAIN --------------------------------------------------------------------------
int main()
{
	
	//VARIABLE DECLARATIONS---------------------------------------------------
	FILE* fRead;
	char line[16];
	char search_str[16];
	
	char* array_ptr;
	char* temp_ptr;



	int i = 0;
	int j = 0;
	int fchar;
	int num_inputs = 0;
	int num_threads;
	int num_slices;
	int slice_size = 0;
	double time;


	//------------------------------------------------------------------------

	//OPEN & ASSIGN FILE POINTER----------------------------------------------
	fRead =  fopen("fartico_aniketsh_input_partA.txt", "r");

	Timer_start();

	//READ FILE TO DETERMINE NUMBER OF STRINGS TO SEARCH -> num_inputs--------
	while(EOF != (fchar = fgetc(fRead)))
		{if ( fchar == '\n'){++num_inputs;}}
	if ( fchar != '\n' ){++num_inputs;}	
	fclose(fRead);

	if ( num_inputs > 4 ) { num_inputs = num_inputs -3; }



	//REOPEN FILE	
	fRead =  fopen("fartico_aniketsh_input_partA.txt", "r");


	//GET NUM THREADS, NUM SLICES, SEARCH STRING------------------------------
	num_threads = fgetc(fRead) - 48;
	fgetc(fRead);
	num_slices = fgetc(fRead) - 48;	
	fgetc(fRead);	
	fgets(search_str, sizeof(search_str), fRead);
	

	//ALLOCATE MEMORY FOR ARRAY AND CREATE TEMP PTR TO ARRAY
	array_ptr = malloc(num_inputs * sizeof(line));
	temp_ptr = array_ptr;

	//SET SIZE OF ARRAY
	slice_size = num_inputs / num_threads;


	//STRCPY FILE INTO ARRAY--------------------------------------------------
	while(fgets(line, sizeof(line), fRead))
	{
		strcpy(&temp_ptr[i*16], line);
		i++;
	}
	//------------------------------------------------------------------------

	Timer_elapsedUserTime(&time);
	
	//PRINT OUT ARRAY---------------------------------------------------------
	while(&temp_ptr[j*16] < &temp_ptr[i*16])
	{
		//printf("%s", &temp_ptr[j*16]);
		j++;
	}	
	//-------------------------------------------------------------------------
	

	printf("\n\nITEMS STORED: %d  ITEMS PRINTED: %d\n",i, j);
	printf("MEMORY USED: %d\n", (&temp_ptr[i*16] - temp_ptr));
	printf("TIME TO STORE: %g\n", time);
	printf("\n\n");
	printf("INPUTS: %d\n", num_inputs);
	printf("THREADS: %d\n", num_threads);
	printf("SLICES: %d\n", num_slices);
	printf("SEARCH STR: %s\n", search_str);
	printf("SIZE OF SLICES: %d\n", slice_size);


	//INITIALIZE THREADS ARRAY & THREAD DATA STRUCT ARRAY---------------------
	
	pthread_t thread_array[num_threads];
	thread_data data_array[num_threads];

	//INITIALIZE STRUCTS-------------------------------------------------------
	int k;
	for( k = 0; k < num_slices; ++k)
	{
		data_array[k].start_ptr = &array_ptr[k * slice_size * 16];
		data_array[k].end_ptr = &array_ptr[(k+1) * slice_size * 16];
		data_array[k].num = k;
		strcpy(data_array[k].match_str, search_str);

	} 

	//INIT MUTEX---------------------------------------------------------------
	pthread_mutex_init(&mutex, NULL);	

	//CREATE THREADS 1 & 2-----------------------------------------------------
	for( k = 0; k < num_slices; ++k)
	{
		pthread_create(&thread_array[k], NULL, (void *) & search_by_thread, (void *) &data_array[k]);
	}

	//WAITS FOR BOTH THREADS TO TERMINATE
	for( k =0; k < num_slices; ++k)
	{
		pthread_join(thread_array[k], NULL);
	}

	//DESTROY MUTEX-------------------------------------------------------------
	pthread_mutex_destroy(&mutex);	


	return 0;
}


void search_by_thread( void* ptr)
{
	//END PTR IS ONE BEYOND WHAT WE WANT TO LOOK AT
	thread_data* data;
	data = (thread_data *) ptr;

	int i = 0;
	char* temp_ptr = data->start_ptr;

	pthread_mutex_lock(&mutex);

	printf("\nTHREAD--------> %d\n", data->num);
	//printf("START: %p\n", data->start_ptr);
	//printf("End  : %p\n", data->end_ptr);
	//printf("Temp : %p\n", temp_ptr);
	//printf("THREAD NUM: %d\n", data->num);
	//printf("FIRST: %s\n", data->start_ptr);
	//printf("Last: %s\n", data->end_ptr-16);

	
	while( &temp_ptr[i*16] < data->end_ptr)
	{
		if( strcmp(&temp_ptr[i*16], data->match_str) == 0)
		{
			printf("Matched Found\n");
		}
		i = i +1;
	}	
	
	printf("Iterations: %d\n", i);

	pthread_mutex_unlock(&mutex);

	pthread_exit(0);
}







