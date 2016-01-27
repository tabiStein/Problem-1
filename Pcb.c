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

const char* stateNames[] = {"Created","Running","Ready","Interrupted","Blocked","Terminated"};

/*char* StateToString(State state) {
	int len = strlen(stateNames[state]);
	char* string = malloc(sizeof(char) * len + 1);
	sprintf(string, "%s", stateNames[state]); //auto appends null at end
	return string;
}*/

void PCBSetPriority(PcbPtr pcb, int priority) {
	pcb->priority = priority;

}

void PCBSetID(PcbPtr pcb, int id) {
	pcb->ID = id;
}

void PCBSetState(PcbPtr pcb, State newState) {
	pcb->state = newState;
}

/**
 * Sets the PC for this PCB.
 */
void PCBSetPC(PcbPtr pcb, unsigned int newPC) {
	pcb->PC = newPC;
}

/**
 * Returns PC of this PCB.
 */
unsigned int PCBGetPC(PcbPtr pcb) {
	return pcb->PC;
}

int PCBGetPriority(PcbPtr pcb) {
	return pcb->priority;
}

int PCBGetID(PcbPtr pcb) {
	return pcb->ID;
}

State PCBGetState(PcbPtr pcb) {
	return pcb->state;
}


 PcbPtr PCBConstructor(){
	PcbPtr pcb = (PcbPtr) malloc(sizeof(PcbStr));
	pcb->ID = 1;
	pcb->priority = 1;
	pcb->state = ready;

	return pcb;
}


char *PCBToString(PcbPtr pcb) {
	char * emptyStr = (char*) malloc(sizeof(char) * 100);
	emptyStr[99] = '\0';
//	int lenNeeded = sprintf(emptyStr, "ID: %d, Priority: %d, State: %s",
//							pcb->ID, pcb->priority, StateToString(pcb->state));
	int lenNeeded = sprintf(emptyStr, "ID: %d, Priority: %d, State: %s, PC: %d",
							pcb->ID, pcb->priority, PCBGetState(pcb), pcb->PC);
	char * retString = (char *) malloc(sizeof(char) * lenNeeded);
	sprintf(retString, "%s", emptyStr);
	free(emptyStr);
	return retString;
}

void PCBDestructor(PcbPtr pcb) {
	free (pcb);
	pcb = NULL;	//Only locally sets the pointer to null
}
