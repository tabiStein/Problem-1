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

Node * nodeConstructor() {
	Node * newNode = (Node*) malloc(sizeof(Node));
	newNode->content = NULL;
	newNode->next = NULL;
	return newNode;
}

Node * nodeDeconstructor(Node * node) {
	Node *nextNode = node->next;

	if (node->content != NULL) {
		PCBDestroy(node->content);
	}
	free (node);
	node = NULL;

	return nextNode;
}

void nodeSetNext(Node * node, Node * nextNode) {
	node->next = nextNode;
}

fifoQueue * fifoQueueConstructor() {
	fifoQueue *newQueue = (fifoQueue*) malloc(sizeof(fifoQueue));
	newQueue->head = NULL;
	newQueue->back = NULL;
	newQueue->size = 0;
	return newQueue;
}

void fifoQueueDestructor(fifoQueue * queue) {
	if (queue->head != NULL) {
		if (queue->head->content == queue->back->content)
			//Destroy(queue->head->content);
			nodeDeconstructor(queue->head);

		else {
			Node * curr = queue->head;
			Node * curr2 = queue->head->next;
			//PcbStr * curr = queue->head;
			//PcbStr * curr2 = queue->head->next;
			while (curr2 != queue->back) {
				//Destroy(curr);
				nodeDeconstructor(curr);
				curr = curr2;
				curr2 = curr2->next;
			}
			nodeDeconstructor(curr);
			nodeDeconstructor(curr2);
			//Destroy(curr);
			//Destroy(curr2);
		}
		queue->size = 0;
		free(queue);
		queue = NULL;
	}
}

void fifoQueueEnqueue(fifoQueue *queue, PcbStr* pcb) {
	if (pcb == NULL) {
		printf("pcb is null");
		return;
	}

	Node * newNode = nodeConstructor();
	newNode->content = pcb;

	if (queue->head == NULL) {
		queue->head = newNode;
		queue->back = newNode;
	}
	else if (queue->head == queue->back) {
		nodeSetNext(queue->head, newNode);
		queue->back = newNode;
	}
	else {
		nodeSetNext(queue->back, newNode);
		queue->back = queue->back->next;
	}
	(queue->size)++;
}


PcbStr *fifoQueueDequeue(fifoQueue *queue) {
	if (queue->head == NULL) {
		printf("Queue is empty");
		return NULL;
	}
	PcbStr * ret = queue->head->content;

	Node * toDestroy = queue->head;
	queue->head = queue->head->next;
	nodeDeconstructor(toDestroy);

	(queue->size)--;
	return ret;
}


PcbPtr fifoQueuePeek(fifoQueue * queue) {
	if (queue->head == NULL) {
		return NULL;
	}
	return queue->head->content;
}

int fifoQueueIsEmpty(fifoQueue * queue) {
	return (queue->head == NULL);
}

int fifoQueueSize() {
	return sizeof(fifoQueue);
}

char *fifoQueueToString(fifoQueue * queue) {
	char * string = malloc(sizeof(char) * (queue->size * 4 + 50));
	string[0]='\0';
	strncat(string, "Q: ", 5);

	if (queue->size == 0) {
		strncat(string, "Empty", 6);
		return string;
	}

	int i;
	Node *front = queue->head;
	for (i = 1; i <= queue->size; i++) {
		char s[5] = "P";
		int j = front->content->ID;
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


