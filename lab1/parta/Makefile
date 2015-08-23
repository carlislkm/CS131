partA: partA.o Timer.o
	gcc partA.o Timer.o -o partA -pthread
partA.o: partA.c
	gcc -c partA.c
Timer.o: Timer.c 
	gcc -c Timer.c
clean:
	rm partA.o Timer.o partA
run: partA
	./partA
