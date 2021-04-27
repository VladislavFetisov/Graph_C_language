

graph: main.o libgraph.a
	gcc -o graph main.o -L. -lgraph 
	del *.o *.a

main.o: main.c
	gcc -c main.c

libgraph.a: graph.o
	ar cr libgraph.a graph.o

graph.o: graph.c
	gcc -c graph.c
	