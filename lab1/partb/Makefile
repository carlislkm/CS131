partB: partB.o Timer.o
	gcc partB.o Timer.o -o partB -pthread
partB.o: partB.c
	gcc -c partB.c
Timer.o: Timer.c 
	gcc -c Timer.c
clean:
	rm partB.o Timer.o partB
run: partB
	./partB
