/*
 * PCB.c
 *
 *  Created on: Jan 6, 2016
 *      Author: Abigail
 */

#include "pcb.h";
#include <stdlib.h>
#include <string.h>

typedef struct {
	int priority;
	int ID;
	PCB * next;
} PCB;

void setPriority(PCB * pcb, int * priority) {
	pcb->priority = *priority;
}

void setID(PCB * pcb, int * id) {
	pcb->ID = *id;
}

void setNext(PCB * pcb, PCB * next) {
	pcb->next = next;
}

int getPriority(PCB * pcb) {
	return pcb->priority;
}

int getID(PCB * pcb) {
	return pcb->ID;
}

PCB *getNext(PCB * pcb) {
	return pcb->next;
}

PCB *newPCB(){
	PCB * pcb = malloc(sizeof(PCB));
	pcb->ID = NULL;
	pcb->priority = NULL;
	pcb->next = NULL;

	return pcb;
}

const char *toString(PCB * pcb) {
	char pcbString[6] = "ID: ";
	strncat(pcbString, "%d", pcb->ID);
	strncat(pcbString, "; Priority: ");
	strncat(pcbString, "%d", pcb->priority);
	strncat(pcbString, "; Next PCB ID: ");
	strncat(pcbString, "%d", ((PCB *) pcb->next)->ID);

	return &pcbString;
}

int *Destroy(PCB * pcb) {
	int * nextPCB = pcb->next;

	free (pcb->ID);
	free (pcb->priority);
	free (pcb);

	return nextPCB;
}
