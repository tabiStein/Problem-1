CC = gcc
CFLAGS = -Wall -g
HEADERS = Pcb.h Fifo.h PriorityQueue.h

all:	priorityQueueTest fifoTest pcbTest

priorityQueueTest:	Pcb.o Fifo.o PriorityQueue.o priorityQueueTest.o
	$(CC) $(CFLAGS) Pcb.o Fifo.o PriorityQueue.o priorityQueueTest.o -o priorityQueueTest
	
fifoTest:	Pcb.o Fifo.o fifoTest.o
	$(CC) $(CFLAGS) Pcb.o Fifo.o fifoTest.o -o fifoTest

pcbTest:	Pcb.o pcbTest.o
	$(CC) $(CFLAGS) Pcb.o pcbTest.o -o pcbTest

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf priorityQueueTest fifoTest pcbTest *.o
