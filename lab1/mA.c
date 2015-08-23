

//Kevin Carlisle 
//Lab 1
//Method A
//CS 131
//
//

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
//#include "Timer.h"
#include <stdlib.h>

int next(FILE* filename)
{
        return getc(filename);
}

int check_c(FILE* filename)
{
        int p = next(filename);
        ungetc(p, filename);
        return p;
}


int main()
{

	FILE* fRead;
	
	char word_buffer[15];
	char* p = word_buffer;
	

	int num_entries = 100000;
	int num_chars = 16;

	char* array_ptr;
	char** row_ptr;

	array_ptr = malloc(num_entries * num_chars * sizeof(char));
	memset(array_ptr, '\0', num_entries * num_chars * sizeof(char));
	row_ptr = malloc(num_entries * sizeof(char));

	//Point the row pointers to the array
	int x;
	for( x = 0; x < num_entries; x++)
	{
		row_ptr[x] = array_ptr + (x * num_chars);
	}

        int c;
	int i = 0;
	int first = 0;
	int count = 0;

        fRead =  fopen("fartico_aniketsh_input_partA.txt", "r");
	
	while( check_c(fRead) != EOF && i < 50)
        {

		first = check_c(fRead);
		
		switch(first)
		{
		case '\n':
			next(fRead);

			*p = '\0';
		
			strcpy(row_ptr[i], word_buffer);
		
			printf("#%d   %p", i, row_ptr[i]);
			printf("      %d", (row_ptr[i] - row_ptr[i-1]));
			printf("      %s      %s\n", word_buffer, row_ptr[i]);
			i++;
		
			memset(word_buffer, 0, sizeof(word_buffer));
			p = word_buffer;
			
			break;
		default:
	
			*p = first;
			p++;
			count++;
			next(fRead);
			break;
		}
        }
	printf("SIZE: %d\n", (row_ptr[i] - row_ptr[0]));
	printf("SIZE / CHAR: %d     Char Count: %d\n", (row_ptr[i] - row_ptr[0])/sizeof(char), count);
        fclose(fRead);
	
	int z = i;
	int f = 0;

//	while( z > 0 )
//	{
		//printf("%s\n", row_ptr[i-z]);
		z--;
//		f++;
//
//	}
	printf("%d----%d\n", i,f);
//	free(row_ptr);
//	free(array_ptr);
	return 0;
}
