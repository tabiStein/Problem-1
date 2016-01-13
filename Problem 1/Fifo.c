/*
 * FIFO.c
 * This is a a linked list ADT that acts as a queue.
 *
 *  Created on: Jan 6, 2016
 *      Author: Sean Markus
 * 
 * Reviewed by: Wing-Sea Poon
 */
#include <stdio.h>
#include <stdlib.h>
#include "Fifo.h"
#include "Pcb.h"
#include <string.h>

fQ * createfQ() {
	/*
	 * the right-hand side needs to be casted to fQ*
	 */
	fQ *newQueue = malloc(sizeof(fQ));
	newQueue->head = NULL;
	newQueue->back = NULL;
	newQueue->size = 0;
	return newQueue;
}

void fQDestructor(fQ * queue) {
	/*
	 * shouldn't this be if (queue->head != NULL) ??
	 */
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
		/*
		 * practice defensive programming by setting "queue = NULL;" after free
		 */
	}
}

void fifoEnqueue(fQ *queue, PcbStr* pcb) {
	/*
	 * There is a possible error here if whoever is using fifoEnqueue() does not call PCB's
	 * constructor. Otherwise, this if-block should be fine.
	 */
	if (queue->head == NULL) {
		queue->head = pcb;
		queue->back = pcb;
	}
	/*
	 * I believe you're missing the case for when the size of the queue is 1; there should
	 * be an if-else block here, because the case for 1 node should be handled differently
	 * from the case when there are multiple nodes
	 */
	else {
		/*
		 * I don't think you're saving the back node? This might cause you the "lose" the
		 * rest of the list.
		 */
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

/*
 * Is this supposed to return the number of elements in the queue? If so, it should take a parameter
 * "fQ* this" and return this->size.
 * If this is supposed to return the amount of memory that an fQ takes up, then this function is
 * correct.
 */
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
