CC = gcc
CFLAGS = -Wall -g
HEADERS = Pcb.h Fifo.h

all:	CPU

CPU:	Pcb.o Fifo.o CPU.o
	$(CC) $(CFLAGS) Pcb.o Fifo.o CPU.o -o CPU

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf CPU *.o
