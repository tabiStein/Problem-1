// Author: Wing-Sea Poon

#ifndef PRIORITY_QUEUE_H
#def PRIORITY_QUEUE_H

#include <stdbool.h>
#include "Fifo.h"
#include "Pcb.h"

#define PRIORITY_LEVELS 16

// Priority Queue ADT
typedef struct 
{
	FIFO priorityArray[PRIORITY_LEVELS];
} PriorityQStr;
typedef PriorityQStr* PriorityQPtr;

// Allocates memory for a Priority Queue object.
PriorityQPtr priorityQConstructor();

// Deallocates memory for a Priority Queue object.
void priorityQDestructor(PriorityQPtr this);

// Adds the PCB to the end of a FIFO queue based on the PCB's priority.
void enqueue(PriorityQPtr this, PCB* pcb);

// Removes and returns the PCB with the highest priority.
PCB* dequeue(PriorityQPtr this);

// Returns, without removing, the PCB with the highest priority.
PCB* peek(PriorityQPtr this);

// Checks whether there are any PCBs in this priority queue.
bool isEmpty(PriorityQPtr this);

// Returns a string representation of this priority queue.
char* toString(PriorityQPtr this);

#endif

