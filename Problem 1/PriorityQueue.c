/*
 * Priority_Queue.c
 *
 *
 *  Created on: Jan 9, 2016
 *      Author: Wing-Sea Poon
 */

#include <stdbool.h>
#include <string.h>

#include "PriorityQueue.h"
#include "Fifo.h"
#include "Pcb.h"


PQPtr pqConstructor()
{
	PQPtr pq = (PQPtr) malloc(sizeof(PQStr));
	if(pq == NULL)
	{
		return NULL;
	}
	
	int i;
	for(i = 0; i < PRIORITY_LEVELS; i++)
	{
		pq->priorityArray[i] = NULL;
	}
	
	return pq;
}

void pqDestructor(PQPtr this)
{
	int i;
	for(i = 0; i < PRIORITY_LEVELS; i++)
	{
		if(this->priorityArray[i] != NULL)
		{
			fqDestructor(this->priorityArray[i]);
		}
	}
	
	free(this);
	this = NULL;
}

void pqEnqueue(PQPtr this, PcbPtr pcb)
{
	fifoEnqueue(this->priorityArray[pcb->priority], pcb);
}

PcbPtr pqDequeue(PQPtr this)
{
	int i;
	PcbPtr retval = NULL;
	
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

PcbPtr pqPeek(PQPtr this)
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

bool pqIsEmpty(PQPtr this)
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

char* pqToString(PQPtr this)
{
	
}


