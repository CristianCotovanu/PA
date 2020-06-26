build: holograme scurt umbre

holograme: graph.o holograme.c
	gcc holograme.c graph.o list.o stack.o queue.o -o holograme -g -Wall -lm

scurt: graph.o scurt.c
	gcc scurt.c graph.o list.o stack.o queue.o -o scurt -g -Wall -lm

umbre: graph.o umbre.c
	gcc umbre.c graph.o list.o stack.o queue.o -o umbre -g -Wall -lm

graph.o: list.o stack.o queue.o heap.o graph.h graph.c
	gcc -c graph.c -g

list.o: list.c list.h
	gcc -c list.c -g

stack.o: stack.c stack.h
	gcc -c stack.c -g

queue.o: queue.c queue.h
	gcc -c queue.c -g

heap.o: heap.c heap.h
	gcc -c queue.c -g

run-p1:
	./holograme
run-p2:
	./scurt
run-p3:
	./umbre

clean:
	rm -f *.o *~ holograme scurt umbre rm *.dot *.png
