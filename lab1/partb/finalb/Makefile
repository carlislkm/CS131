ProgramB: ProgramB.o 
	gcc ProgramB.o -o ProgramB -pthread
partB.o: ProgramB.c
	gcc -c ProgramB.c
clean:
	rm ProgramB.o ProgramB
run: ProgramB
	./ProgramB
