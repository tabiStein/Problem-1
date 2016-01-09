/*
 * FIFO.c
 * This is a a linked list ADT that acts as a queue.
 * I don't really know what a pcb is but this can hold them.
 *
 *  Created on: Jan 6, 2016
 *      Author: Sean
 */
#include <stdio.h>
#include "FIFO.h"
#include "pcb.h"

//node * head = NULL;

void enqueue(Queue *queue, PCB *pcb) {
	Node *newNode = malloc(sizeof(Node));
	newNode->myPcb = pcb;
	newNode->next = NULL;
	if (queue->head == NULL) {
		queue->head = newNode;
		return;
	}
	Node * curr = queue->head;
	while (curr->next != NULL) {
		curr = curr->next;
	}
	curr->next = newNode;
}

PCB *dequeue(Queue *queue) {
	if (queue->head == NULL) {
		printf("Queue is empty");
		return NULL;
	}
	Node * curr = queue->head;
	while (curr->next != NULL)
		curr = curr->next;
	PCB * ret = curr->myPcb;
	free(curr);
	return ret;
}

PCB *peek(Queue * queue) {
	if (queue->head == NULL) {
		printf("Queue is empty");
		return NULL;
	}
	return queue->head->myPcb;
}
