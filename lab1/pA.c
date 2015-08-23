//Kevin Carlisle
//CS131 
//Lab 1
//April 10, 2015

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>


int main()
{

	FILE* fRead;
	fRead =  fopen("fartico_aniketsh_input_partA.txt", "r");

	char word_array[1000][3] = {'a','b','\0'};
	
	int i = 0;

	while ( i < 1000)
	{
		printf("%s\n", word_array[1]);
		i++;

	}

	fclose(fRead);

	return 0;

}
