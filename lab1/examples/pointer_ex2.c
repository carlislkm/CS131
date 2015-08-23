#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>



int main()
{

	FILE* fRead;
	char line[16];
	
	char* array_ptr;
	char* temp_ptr;
	char* temp2_ptr;
	char* temp3_ptr;

	array_ptr = malloc(1600048);
	temp_ptr = array_ptr;
	temp2_ptr = array_ptr;
	temp3_ptr = array_ptr;

	int i = 0;
	int j = 0;


	fRead =  fopen("fartico_aniketsh_input_partA.txt", "r");
	

	while(fgets(line, sizeof(line), fRead))
	{
		//strcpy(temp_ptr + (i*16), line);
		//printf("%p  %p\n",temp_ptr, &temp2_ptr[i*16]); 
		//strcpy(temp_ptr, line);
		strcpy(&temp2_ptr[i*16], line);
		//temp_ptr = temp_ptr + 16;
		i++;
	}
	printf("\n");

	
	while(&temp2_ptr[j*16] < &temp2_ptr[i*16])
	{
		printf("%s", &temp2_ptr[j*16]);
		j++;
	}	
	printf("\nJ: %d  I: %d\n",j, i);

	


	return 0;
}
