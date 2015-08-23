ProgramA: ProgramA.o
	gcc ProgramA.o -o ProgramA -pthread
partA.o: ProgramA.c
	gcc -c ProgramA.c
clean:
	rm ProgramA.o ProgramA
run: ProgramA
	./ProgramA
