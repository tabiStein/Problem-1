/*
 * FIFO.h
 *
 *  Created on: Jan 7, 2016
 *      Author: Sean
 */

#ifndef FIFO_H_
#define FIFO_H_
#include "Pcb.h"

/**
 * Node object for when this was going to be a linkedlist.
 * I guess we'll be using PCBs to have next instead though?
 */
typedef struct node {
	PCB *myPcb;
	struct node * next;
} Node;

/**
 * The queue ADT.
 * Holds one PCB in each linked nodes or maybe just the linked PCBs
 * when I see what they look like
 */
typedef struct queue {
	Node * head;
}Queue;

/**
 * Pass in the queue and a pointer of the PCB to enqueue
 */
void enqueue(Queue *queue, PCB *pcb);

/**
 * Pass in a queue. Returns and dequeues the head PCB.
 */
PCB *dequeue(Queue *queue);

/**
 * Returns a pointer to the head PCB
 * Should this just be a copy?
 */
PCB *peek(Queue * queue);

/**
 * Is it Empty?
 */
int isEmpty();

/**
 * Returns a formatted string of all PCBs and their content
 */
char * toString();

#endif /* FIFO_H_ */
