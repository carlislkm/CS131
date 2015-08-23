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


	fRead =  fopen("fartico_aniketsh_input_partA.txt", "r");
	

	while(fgets(line, sizeof(line), fRead))
	{
		//strcpy(temp_ptr + (i*16), line);
		//i++;
		strcpy(temp_ptr, line);
		temp_ptr = temp_ptr + 16;
	}
	printf("\n");
	//temp_ptr = temp_ptr + 16;

	i = 0;
	//while( (temp2_ptr + (i*16)) < temp_ptr)
	//while(temp2_ptr < temp_ptr)
	while(&temp2_ptr[i*16] < temp_ptr)
	{
		//printf("%s", temp2_ptr + (i*16));
		//printf("%s", temp2_ptr);
		//printf("%p___%p\n", (temp3_ptr + (i*16)), temp2_ptr);
		//printf("--%s\n", (char*)&temp3_ptr[i*16]);
		//printf("--%p\n", &temp3_ptr[i*16]);
		//temp2_ptr = temp2_ptr + 16;
		printf("%s", &temp2_ptr[i*16]);
		i++;
	}	
	printf("\nI: %d\n", i);

	


	return 0;
}
