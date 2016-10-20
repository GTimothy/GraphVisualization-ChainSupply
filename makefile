
executable : graphes.o courtChemin.o printGraph.o main.o
	gcc -g graphes.o courtChemin.o printGraph.o main.o -o executable
graphes.o: graphes.h graphes.c
	gcc -g -c graphes.c
courtChemin.o: graphes.h courtChemin.c
	gcc -g -c courtChemin.c
printGraph.o: graphes.h printGraph.c
	gcc -g -c printGraph.c
main.o: graphes.h main.c  
	gcc -g -c main.c 

clean:
	rm -rf *.o

mrproper: clean
	rm -rf executable

