// Author: Wing-Sea Poon

#ifndef PRIORITY_QUEUE_H

#def PRIORITY_QUEUE_H

#define PRIORITY_LEVELS = 16;

// Priority Queue ADT
typedef struct 
{
	FIFO priority_array[PRIORITY_LEVELS];
} Priority_Str;
typedef Priority_Str* Priority_Ptr;

// Adds the PCB to the end of a FIFO queue based on the PCB's priority.
void enqueue(PCB* pcb);

// Removes and returns the PCB with the highest priority.
PCB* dequeue();

// Returns, without removing, the PCB with the highest priority.
PCB* peek();

// Checks whether there are any PCBs in this priority queue.
bool isEmpty();

// Returns a string representation of this priority queue.
char* toString();

#endif

