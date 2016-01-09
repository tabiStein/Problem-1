/*
 * Priority_Queue.c
 *
 *
 *  Created on: Jan 9, 2016
 *      Author: Wing-Sea Poon
 */


#include <stdbool.h>
#include <stdio.h>

#include "Priority_Queue.h"
#include "FIFO.h"
#include "pcb.h"

void enqueue(PCB* pcb)
{
	priority_array[pcb.getPriority()].enqueue(&pcb);
}

PCB* dequeue()
{
	int i;
	PCB* retval = NULL;
	
	for(i = 0; i < PRIORITY_LEVELS; i++)
	{
		if(priority_array[i] != NULL)
		{
			retval = priority_array[i].dequeue();
			break;
		}
	}
	
	return retval;
}

PCB* peek()
{
	int i;
	for(i = 0; i < PRIORITY_LEVELS; i++)
	{
		if(priority_array[i] != NULL)
		{
			return priority_array[i];
		}
	}
	
	return NULL;
}

bool isEmpty()
{
	int i;
	for(i = 0; i < PRIORITY_LEVELS; i++)
	{
		if(priority_array[i] != NULL)
		{
			return false;
		}
	}
	
	return true;
}

char* toString()
{
	
}
