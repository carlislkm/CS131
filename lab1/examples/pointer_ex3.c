#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>



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
	//------------------------------------------------------------------------

	//OPEN & ASSIGN FILE POINTER----------------------------------------------
	fRead =  fopen("fartico_aniketsh_input_partA.txt", "r");
	

	//STRCPY FILE INTO ARRAY--------------------------------------------------
	while(fgets(line, sizeof(line), fRead))
	{
		strcpy(&temp_ptr[i*16], line);
		i++;
	}
	//------------------------------------------------------------------------

	
	//PRINT OUT ARRAY---------------------------------------------------------
	while(&temp_ptr[j*16] < &temp_ptr[i*16])
	{
		printf("%s", &temp_ptr[j*16]);
		j++;
	}	
	printf("\nJ: %d  I: %d\n",j, i);
	//-------------------------------------------------------------------------
	










	return 0;
}
