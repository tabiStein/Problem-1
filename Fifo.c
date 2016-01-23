/***********************************************************************************************
* Fifo.c
*
* Programming Team:
* Sean Markus
* Wing-Sea Poon
* Abigail Smith
* Tabi Stein
*
* Date: 1/22/16
*
* Description:
* This C file implements the class and methods for the FIFO Queue.
*
************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "Fifo.h"
#include "Pcb.h"
#include <string.h>

fQ * createfQ() {
	fQ *newQueue = (fQ*) malloc(sizeof(fQ));
	newQueue->head = NULL;
	newQueue->back = NULL;
	newQueue->size = 0;
	return newQueue;
}

void fQDestructor(fQ * queue) {
	/*
	 * shouldn't this be if (queue->head != NULL) ??
	 */
	if (queue->head != NULL) {
		if (queue->head == queue->back)
			Destroy(queue->head);
		else {
			PcbStr * curr = queue->head;
			PcbStr * curr2 = queue->head->next;
			while (curr2 != queue->back) {
				Destroy(curr);
				curr = curr2;
				curr2 = curr2->next;
			}
			Destroy(curr);
			Destroy(curr2);
		}
		queue->size = 0;
		free(queue);
		queue = NULL;
	}
}

void fifoEnqueue(fQ *queue, PcbStr* pcb) {
	if (pcb == NULL) {
		printf("pcb is null");
		return;
	}
	if (queue->head == NULL) {
		queue->head = pcb;
		queue->back = pcb;
	}
	else if (queue->head == queue->back) {
		setNext(queue->head, pcb);
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


PcbPtr fifoPeek(fQ * queue) {
	if (queue->head == NULL) {
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
	PcbStr *front = queue->head;
	for (i = 1; i <= queue->size; i++) {
		char s[5] = "P";
		int j = front->ID;
		int numWritten = sprintf(s + 1, "%d", j); //For i > 9, we go into ascii vals above val for char '9'
		s[numWritten + 1] = '-';
		strncat(string, s, 5);
		front = front->next;
	}

	/*
	strncat(string, "* : contents: ", 15);
	PcbStr *curr = queue->back;
	strncat(string, toString(curr), 100);
	*/
	return string;
}

