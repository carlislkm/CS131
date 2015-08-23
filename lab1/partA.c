#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "Timer.h"


int main()
{
	
	//VARIABLE DECLARATIONS---------------------------------------------------
	FILE* fRead;
	char line[16];
	
	char* array_ptr;
	char* temp_ptr;

	array_ptr = malloc(1600048);
	temp_ptr = array_ptr;

	int i = 0;
	int j = 0;
	double time;
	//------------------------------------------------------------------------

	//OPEN & ASSIGN FILE POINTER----------------------------------------------
	fRead =  fopen("fartico_aniketsh_input_partA.txt", "r");

	Timer_start();

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
		printf("%s", &temp_ptr[j*16]);
		j++;
	}	
	//-------------------------------------------------------------------------
	

	printf("\n\nITEMS STORED: %d  ITEMS PRINTED: %d\n",i, j);
	printf("MEMORY USED: %d\n", (&temp_ptr[i*16] - temp_ptr));
	printf("TIME TO STORE: %g\n", time);


	return 0;
}
