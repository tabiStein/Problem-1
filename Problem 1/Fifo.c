/*
 * FIFO.c
 * This is a a linked list ADT that acts as a queue.
 *
 *  Created on: Jan 6, 2016
 *      Author: Sean
 */
#include <stdio.h>
#include <stdlib.h>
#include "Fifo.h"
#include "pcb.h"
#include <string.h>

Queue * createQueue() {
	Queue *newQueue = malloc(sizeof(Queue));
	newQueue->head = NULL;
	newQueue->back = NULL;
	newQueue->size = 0;
	return newQueue;
}

void destroyQueue(Queue * queue) {
	if (queue->head == NULL) {
		if (queue->head == queue->back)
			Destroy(queue->head);
		PCB * curr = queue->head;
		PCB * curr2 = queue->head->next;
		while (curr2->next != queue->back) {
			Destroy(curr);
			curr = curr2;
			curr2 = curr2->next;
		}
		queue->size = 0;
		free(queue);
	}
}

void fifoEnqueue(Queue *queue, PCB * pcb) {
	if (queue->head == NULL) {
		queue->head = pcb;
		queue->back = pcb;
	}
	else {
		setNext(pcb, queue->back);
		queue->back = queue->back->next;
	}
	(queue->size)++;
}

PCB *fifoDequeue(Queue *queue) {
	if (queue->head == NULL) {
		printf("Queue is empty");
		return NULL;
	}
	PCB * ret = queue->head;
	queue->head = queue->head->next;

	(queue->size)--;
	return ret;
}

PCB *peek(Queue * queue) {
	if (queue->head == NULL) {
		printf("Queue is empty");
		return NULL;
	}
	return queue->head;
}

char *toStringQueue(Queue * queue) {
	char string = malloc(sizeof(char) * (queue->size * 4 + 50));
	char w[5] = "Q: ";
	strncat(string, w, 5);
	if (queue->size == 0) {
		strncat(string, "Empty", 6);
		return string;
	}
	int i;
	for (i = 1; i <= queue->size; i++) {
		char s[5] = "P";
		s[1] = i;
		s[2] = '-';
		strncat(string, s, 5);
	}
	PCB *curr = queue->head;
	strncat(string, toString(curr), 100);
	return string;
}
