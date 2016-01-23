/***********************************************************************************************
* Pcb.c
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
* This C file implements the class and methods for the process control block.
*
************************************************************************************************/

#include "Pcb.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
typedef struct {
	int priority;
	int ID;
	struct PCB * next;
} PCB;
*/

void setPriority(PcbPtr pcb, int priority) {
	pcb->priority = priority;

}

void setID(PcbPtr pcb, int id) {
	pcb->ID = id;
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

 PcbPtr getNext(PcbPtr pcb) {
	return pcb->next;
}

 PcbPtr newPCB(){
	PcbPtr pcb = (PcbPtr) malloc(sizeof(PcbStr));
	pcb->ID = 1;
	pcb->priority = 1;
	pcb->next = NULL;

	return pcb;
}

char *toString(PcbPtr pcb) {
	char * emptyStr = (char*) malloc(sizeof(char) * 100);
	emptyStr[99] = '\0';
	int lenNeeded = sprintf(emptyStr, "ID: %d, Priority: %d, Next PCB ID: ", pcb->ID, pcb->priority);

	char * nextIDString = (char*)malloc(sizeof(char) * 5);
	sprintf(nextIDString, "NULL");

	if (pcb->next != NULL) {
		nextIDString = (char *) malloc(sizeof(char) * 100);
		sprintf(nextIDString, "%d", pcb->next->ID);
	}
	int addedLen = strlen(nextIDString);
	char * retString = (char *) malloc(sizeof(char) * (lenNeeded + addedLen));
	sprintf(retString, "%s %s", emptyStr, nextIDString);
	free(emptyStr);
	free(nextIDString);
	return retString;

}

PcbPtr Destroy(PcbPtr pcb) {
	PcbPtr nextPCB = pcb->next;
	//free (pcb->ID);
	//free (pcb->priority);
	free (pcb);
	pcb = NULL;
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
