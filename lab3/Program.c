// Kevin Carlisle
// CS131
// Lab 3
// Parts A and B
// June 5th 2015

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define SIZE 15

int main(int argc, char* argv[])
{
    char* arrayPtr = NULL;
    char* tempPtr = NULL;
    FILE* fRead;
    FILE* fWrite;
    char inFile[128];
    char outFile[128];
    char searchStr[SIZE];
    char line[SIZE];
    int i = 0;
    int numInputs = 0;
    int numThreads = 0;
    int sliceSize = 0;
    int fChar;    
    int tid;


    if (argc == 1){
        strcpy(inFile,"fartico_aniketsh_input_partA.txt");
        strcpy(outFile, "default_outputfile.txt");
                    }
    else if ( argc = 5 ) {
        strcpy(inFile,argv[1]);
        strcpy(outFile,argv[2]);
        numThreads = atoi(argv[3]);
        sliceSize = 100000/atoi(argv[4]);}
    else { exit(1);} 

    // OPEN FILE
    fRead = fopen(inFile, "r");
    // ENSURE FILE OPEN
    if( fRead == NULL){perror("FILE OPEN FAILED\n");
        exit(1);}
        
    // READ REMAINING LINES IN FILE AND STORE COUNT
    //INTO VARIABLE (INT) --> NUM_INPUTS
    while(EOF != (fChar = fgetc(fRead)))
        {if ( fChar == '\n'){++numInputs;}}
    if ( fChar != '\n' ){++numInputs;}
    if (numInputs > 4) {numInputs = numInputs -3;}
    
    // CLOSE FILE
    fclose(fRead);
    // REOPEN FILE, ENSURE OPEN
    fRead = fopen(inFile, "r");
    //ENSURE FILE OPEN
    if (fRead == NULL){perror("FILE OPEN FAILED\n");
        exit(1);}

    
    fgets(searchStr, sizeof(searchStr), fRead);
    //numThreads = atoi(searchStr);
    fgets(searchStr, sizeof(searchStr), fRead);
    //numSlices = atoi(searchStr);
    fgets(searchStr, sizeof(searchStr), fRead);
                                                         
    // Declare array to store input file
        // Size (NumInputs * Size Of Line( 15 Chars)
    arrayPtr = malloc(numInputs * sizeof(line));
    memset(arrayPtr, '\0', numInputs * sizeof(line));
    tempPtr = arrayPtr;

    // Strcpy into Array
    while( fgets(line, sizeof(line), fRead))
    {
        strcpy(&tempPtr[i * SIZE], line);
        i++;
    }
    
    // Test if Sucessful
    //int j;
    //for ( j = 0; j < numInputs; j++){printf("%s\n", &arrayPtr[j * SIZE]);} 
    //printf("NUM THREADS: %d\n", numThreads);
    //printf("NUM SLICES: %d\n", numSlices);

    i = 0;
    int posFoundS = -1;
    int processFoundS = -1;
    int sliceNum = -1;
    int posFoundD = -1;
    int processFoundD = -1;
    #pragma omp parallel shared(searchStr, sliceSize) private(i, tid) num_threads(numThreads)
    {
        tid = omp_get_thread_num();
        
    #pragma omp for schedule( static, sliceSize)
        for (i= 0; i < numInputs; i++)
        {
            if( strcmp (&arrayPtr[i * SIZE], searchStr) == 0)
            {
                posFoundS = i;// + (tid*sliceSize);
                processFoundS = tid;
                sliceNum = i / sliceSize;
            }
        }
    }// END OF STATIC PRAGMA
    fWrite = fopen(outFile, "w");
    fprintf(fWrite, "Part A\n");
    fprintf(fWrite, "PROCESS: %d FOUND: %d Slice:%d \n", processFoundS, posFoundS, sliceNum);
    #pragma omp parallel shared(searchStr, sliceSize) private(i, tid) 
    {
    tid = omp_get_thread_num();
    #pragma omp for schedule( dynamic, sliceSize)
        
        for (i= 0; i < numInputs; i++)
        {
            if( strcmp (&arrayPtr[i * SIZE], searchStr) == 0)
            {
                posFoundD = i;// + (tid*sliceSize);
                processFoundD = tid;
            }
        }
    }
    fprintf(fWrite, "\nPart B\n");
    fprintf(fWrite,"PROCESS: %d FOUND: %d \n", processFoundD, posFoundD);
}