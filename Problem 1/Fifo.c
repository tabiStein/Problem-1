/*
 * FIFO.c
 * This is a a linked list ADT that acts as a queue.
 *
 *  Created on: Jan 6, 2016
 *      Author: Sean Markus
 */
#include <stdio.h>
#include <stdlib.h>
#include "Fifo.h"
#include "Pcb.h"
#include <string.h>

fQ * createfQ() {
	fQ *newQueue = malloc(sizeof(fQ));
	newQueue->head = NULL;
	newQueue->back = NULL;
	newQueue->size = 0;
	return newQueue;
}

void fQDestructor(fQ * queue) {
	if (queue->head == NULL) {
		if (queue->head == queue->back)
			Destroy(queue->head);
		PcbStr * curr = queue->head;
		PcbStr * curr2 = queue->head->next;
		while (curr2->next != queue->back) {
			Destroy(curr);
			curr = curr2;
			curr2 = curr2->next;
		}
		queue->size = 0;
		free(queue);
	}
}

void fifoEnqueue(fQ *queue, PcbStr* pcb) {
	if (queue->head == NULL) {
		queue->head = pcb;
		queue->back = pcb;
	}
	else {
		setNext(queue->back, pcb);
		queue->back = queue->back->next;
	}
	(queue->size)++;
}

PcbStr *fifoDequeue(fQ *queue) {
	if (queue->head == NULL) {
		printf("Queue is empty");
		return NULL;
	}
	PcbStr * ret = queue->head;
	queue->head = queue->head->next;

	(queue->size)--;
	return ret;
}

PcbStr *fifoPeek(fQ * queue) {
	if (queue->head == NULL) {
		printf("Queue is empty");
		return NULL;
	}
	return queue->head;
}

int fifoIsEmpty(fQ * queue) {
	return (queue->head == NULL);
}

int fQSize() {
	return sizeof(fQ);
}

char *fifoToString(fQ * queue) {
	char * string = malloc(sizeof(char) * (queue->size * 4 + 50));
	string[0]='\0';
	strncat(string, "Q: ", 5);

	if (queue->size == 0) {
		strncat(string, "Empty", 6);
		return string;
	}

	int i;
	for (i = 1; i <= queue->size; i++) {
		char s[5] = "P";
		s[1] = '0' + i;
		s[2] = '-';
		strncat(string, s, 5);
	}
	strncat(string, "* : contents: ", 15);
	PcbStr *curr = queue->back;
	strncat(string, toString(curr), 100);
	return string;
}
