priorityQueueTest:	Pcb.o Fifo.o PriorityQueue.o priorityQueueTest.o
	gcc -Wall -g -o priorityQueueTest Pcb.o Fifo.o PriorityQueue.o priorityQueueTest.o
	
fifoTest:	Pcb.o Fifo.o fifoTest.o
	gcc -Wall -g -o fifoTest Pcb.o Fifo.o fifoTest.o

pcbTest:	Pcb.o pcbTest.o
	gcc -Wall -g -o pcbTest Pcb.o pcbTest.o

priorityQueueTest.o:	priorityQueueTest.c
	gcc -Wall -g -c priorityQueueTest.c
	
fifoTest.o:	fifoTest.c
	gcc -Wall -g -c fifoTest.c
	
pcbTest.o:	pcbTest.c
	gcc -Wall -g -c pcbTest.c
	
PriorityQueue.o:	PriorityQueue.c
	gcc -Wall -g -c PriorityQueue.c

Fifo.o:	Fifo.c
	gcc -Wall -g -c Fifo.c
	
Pcb.o:	Pcb.c
	gcc -Wall -g -c Pcb.c

clean:
	rm -rf priorityQueueTest fifoTest pcbTest *.o
