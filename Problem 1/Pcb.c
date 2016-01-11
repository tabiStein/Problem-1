/*
 * PCB.c
 *
 *  Created on: Jan 6, 2016
 *      Author: Abigail
 */

#include "Pcb.h"
#include <stdlib.h>
#include <string.h>

/*
typedef struct {
	int priority;
	int ID;
	struct PCB * next;
} PCB;
*/

void setPriority(PcbPtr pcb, int * priority) {
	pcb->priority = priority;

}

void setID(PcbPtr pcb, int * id) {
	pcb->ID = *id;
}

void setNext(PcbPtr pcb, PcbPtr next) {
	pcb->next = next;
}

int getPriority(PcbPtr pcb) {
	return pcb->priority;
}

int getID(PcbPtr pcb) {
	return pcb->ID;
}

struct PcbStr *getNext(PcbPtr pcb) {
	return pcb->next;
}

struct PcbStr *newPCB(){
	PcbPtr pcb = (PcbPtr) malloc(sizeof(PcbStr));
	pcb->ID = NULL;
	pcb->priority = NULL;
	pcb->next = NULL;

	return pcb;
}

const char *toString(PcbPtr pcb) {
	char pcbString[6] = "ID: ";
	strncat(pcbString, "%d", pcb->ID);
	strncat(pcbString, "; Priority: ", 10);
	strncat(pcbString, "%d", pcb->priority);
	strncat(pcbString, "; Next PCB ID: ", 15);

	strncat(pcbString, "%d", ((PcbStr) pcb->next)->ID);

	return &pcbString;
}

int *Destroy(PcbPtr pcb) {
	int * nextPCB = pcb->next;

	free (pcb->ID);
	free (pcb->priority);
	free (pcb);

	return nextPCB;
}

/*
int main() {
	PCB * pcb1;
	pcb1 = newPCB();
	pcb1->ID = 123;
	pcb1->priority = 3;

	PCB * pcb2;
	pcb2 = newPCB();
	pcb2->ID = 456;
	pcb2->priority = 5;

	pcb1->next = pcb2;

	printf("%s\n",toString(pcb1));

	return 0;
}
*/
