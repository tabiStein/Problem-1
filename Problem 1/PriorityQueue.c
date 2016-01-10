/*
 * Priority_Queue.c
 *
 *
 *  Created on: Jan 9, 2016
 *      Author: Wing-Sea Poon
 */


// Author: Wing-Sea Poon
#include <stdbool.h>
#include <string.h>

#include "PriorityQueue.h"
#include "Fifo.h"
#include "Pcb.h"


PriorityQPtr priorityQConstructor()
{
	
}

void priorityQDestructor(PriorityQPtr this)
{
	
}

void enqueue(PriorityQPtr this, PCB* pcb)
{
	fifoEnqueue(this->priorityArray[pcb.priority], pcb);
}

PCB* dequeue(PriorityQPtr this)
{
	int i;
	PCB* retval = NULL;
	
	for(i = 0; i < PRIORITY_LEVELS; i++)
	{
		if(this->priorityArray[i] != NULL)
		{
			retval = fifoDequeue(this->priority_array[i]);
			break;
		}
	}
	
	return retval;
}

PCB* peek(PriorityQPtr this)
{
	int i;
	for(i = 0; i < PRIORITY_LEVELS; i++)
	{
		if(this->priorityArray[i] != NULL)
		{
			return priorityArray[i];
		}
	}
	
	return NULL;
}

bool isEmpty(PriorityQPtr this)
{
	int i;
	for(i = 0; i < PRIORITY_LEVELS; i++)
	{
		if(this->priorityArray[i] != NULL)
		{
			return false;
		}
	}
	
	return true;
}

char* toString(PriorityQPtr this)
{
	
}

