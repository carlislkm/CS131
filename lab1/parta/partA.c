#include <string.h>		//String Handling
#include <stdlib.h>		//General Utilities
#include <stdio.h>		//Input / Output	
#include <fcntl.h>
#include <unistd.h>		//Symbolic Constants
#include <sys/types.h>          //Primitive System Data Types
#include <errno.h>		//ERRORS
#include <pthread.h>		//POSIX THREADS

//Kevin Carlisle
//CS 131
//Lab 1
//Part A

#define SIZE 15

//PROTOTYPE FOR THREAD ROUTINE
void search_by_thread( void* ptr);

//STRUCT TO STORE DATA TO PASS TO THREAD FUNCTION
typedef struct thread_struct
{
	char* start_ptr;
	char* end_ptr;
	int thread_id;
	int slice_size;
	char match_str[SIZE];

} thread_data;

pthread_mutex_t mutex;

//MAIN --------------------------------------------------------------------------
int main()
{
	
	//VARIABLE DECLARATIONS---------------------------------------------------
	FILE* fRead;
	char line[SIZE];
	char search_str[SIZE];
	char* array_ptr;
	char* temp_ptr;
	int i = 0;
	int j = 0;
	int fchar;
	int num_inputs = 0;
	int num_threads;
	int num_slices;
	int slice_size = 0;
	char file_name[] = "fartico_aniketsh_input_partA.txt";
        char alt_file[128];

        //PROMPT FOR DIFFERENT FILE
        printf("\n(fartico_aniketsh_input_partA.txt)\n");
        printf("ENTER ALT FILENAME OR (ENTER TO RUN): ");
        gets(alt_file);
	printf("\n");
        
        if(strcmp(alt_file, "") != 0)
        {
        	strcpy(file_name, alt_file);
        }                                                                

	//OPEN & ASSIGN FILE POINTER----------------------------------------------
	fRead =  fopen(file_name, "r");
	if(fRead == NULL)
        {
                perror("FILE OPEN FAILED\n");
                exit(1);
        }

	//READ FILE TO DETERMINE NUMBER OF STRINGS TO SEARCH -> num_inputs--------
	while(EOF != (fchar = fgetc(fRead)))
		{if ( fchar == '\n'){++num_inputs;}}
	if ( fchar != '\n' ){++num_inputs;}	
	fclose(fRead);

	if ( num_inputs > 4 ) { num_inputs = num_inputs -3; }

	//REOPEN FILE	
	fRead =  fopen(file_name, "r");
	if(fRead == NULL)
        {
                perror("FILE OPEN FAILED\n");
                exit(1);
        }

	//GET NUM THREADS, NUM SLICES, SEARCH STRING------------------------------
	fgets(search_str, sizeof(search_str), fRead);
	num_threads = atoi(search_str);
	fgets(search_str, sizeof(search_str), fRead);
	num_slices = atoi(search_str);
	fgets(search_str, sizeof(search_str), fRead);

	//ALLOCATE MEMORY FOR ARRAY AND CREATE TEMP PTR TO ARRAY
	array_ptr = malloc(num_inputs * sizeof(line));
	memset(array_ptr, '\0', num_inputs * sizeof(line));
	temp_ptr = array_ptr;

	//SET SIZE OF SLICES
	slice_size = num_inputs / num_slices;
	
	//STRCPY FILE INTO ARRAY--------------------------------------------------
	while(fgets(line, sizeof(line), fRead))
	{
		strcpy(&temp_ptr[i*SIZE], line);
		i++;
	}

	//INITIALIZE THREADS ARRAY & THREAD DATA STRUCT ARRAY---------------------
	pthread_t thread_array[num_threads];
	thread_data data_array[num_threads];

	//INITIALIZE STRUCTS-------------------------------------------------------
	int k;
	for( k = 0; k < num_threads; ++k)
	{
		data_array[k].start_ptr = &array_ptr[k * slice_size * SIZE];
		data_array[k].end_ptr = &array_ptr[(k+1) * slice_size * SIZE];
		data_array[k].thread_id = k;
		data_array[k].slice_size = slice_size;
		strcpy(data_array[k].match_str, search_str);

	} 

	//INIT MUTEX---------------------------------------------------------------
	pthread_mutex_init(&mutex, NULL);	

	//CREATE THREADS 1 & 2-----------------------------------------------------
	for( k = 0; k < num_threads; ++k)
	{
		pthread_create(&thread_array[k], NULL, (void *) & search_by_thread, (void *) &data_array[k]);
	}

	//WAITS FOR BOTH THREADS TO TERMINATE
	for( k =0; k < num_threads; ++k)
	{
		pthread_join(thread_array[k], NULL);
	}

	//DESTROY MUTEX-------------------------------------------------------------
	pthread_mutex_destroy(&mutex);	

	printf("\n");

	return 0;
}

void search_by_thread( void* ptr)
{
	//END PTR IS ONE BEYOND WHAT WE WANT TO LOOK AT
	thread_data* data;
	data = (thread_data *) ptr;

	int i = 0;
	int position_i = -1;
	int slice_i = -1;
	char found_i[] = "no";
	char* temp_ptr = data->start_ptr;
	
	while( &temp_ptr[i*SIZE] < data->end_ptr)
	{
		if( strcmp(&temp_ptr[i*SIZE], data->match_str) == 0)
		{
			//printf("Matched Found\n");
			position_i = (data->thread_id * data->slice_size) + i;
			slice_i = data->thread_id;
			strcpy(found_i, "yes");
		}
		i = i +1;
	}	
	//LOCK
	pthread_mutex_lock(&mutex);
	printf("thread %d, found %s, slice %d, position %d\n", data->thread_id,found_i, slice_i, position_i);
	pthread_mutex_unlock(&mutex);
	//UNLOCK
	
	pthread_exit(0);
}







