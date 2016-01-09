/*
 * PCB.c
 *
 *  Created on: Jan 6, 2016
 *      Author: Abigail
 */

#include "pcb.h";
#include <stdlib.h>

void setPriority(PCB * pcb, int * priority) {
	pcb->priority = *priority;
}

void setID(PCB * pcb, int * id) {
	pcb->ID = *id;
}

void setNext(PCB * pcb, int * next) {
	pcb->next = next;
}

const char *toString(PCB * pcb) {
	char pcbString[] = "ID: " + pcb->ID + "; Priority: " + pcb->priority +
			"; Next PCB ID: " + ((PCB *) pcb->next)->ID;

	return pcbString;
}

int *Destroy(PCB * pcb) {
	int * nextPCB = pcb->next;

	free (pcb->ID);
	free (pcb->priority);
	free (pcb);

	return nextPCB;
}
