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
#include <time.h>

const char* stateNames[] = {"Created","Running","Ready","Interrupted","Blocked","Terminated"};

char* StateToString(State state) {
	int len = strlen(stateNames[state]);
	char* string = malloc(sizeof(char) * len + 1);
	sprintf(string, "%s", stateNames[state]); //auto appends null at end
	return string;
}

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

/*
char* PCBGetState(PcbPtr pcb) {
	State myState = pcb->state;
	switch (myState){
		case created: return "Created";
		case running: return "Running";
		case ready: return "Ready";
		case interrupted: return "Interrupted";
		case blocked: return "Blocked";
		case terminated: return "Terminated";
	}
	return "No State";
}*/


 PcbPtr PCBConstructor(){
	//srand(time(NULL));
	PcbPtr pcb = (PcbPtr) malloc(sizeof(PcbStr));
	pcb->ID = 1;
	pcb->PC = 0;
	pcb->priority = 1;
	pcb->state = created;


	pcb->MAX_PC = rand()%2000 + 1000; //should range from 1000-3000

	pcb->CREATION = (double)clock();

	pcb->TERMINATE = rand()%30;	//ranges from 0-30
	pcb->TERM_COUNT = 0;
	pcb->IO_1_TRAPS = (int*) malloc(4*sizeof(int));
	pcb->IO_2_TRAPS = (int*) malloc(4*sizeof(int));

	genIOArrays(pcb);

	return pcb;
}

 void genIOArrays(PcbPtr pcb) {
	int quarterMax = pcb->MAX_PC/4;


	pcb->IO_1_TRAPS[0] = rand()%quarterMax;//generate a random number that's in the first 1/4 of MAX_PC
	pcb->IO_1_TRAPS[1] = rand()%quarterMax + quarterMax;//random number between 1/4-2/4 of MAX_PC
	pcb->IO_1_TRAPS[2] = rand()%quarterMax + 2 * quarterMax;//random number between 2/4-3/4 of MAX_PC
	pcb->IO_1_TRAPS[3] = rand()%quarterMax + 3 * quarterMax;//random number between 3/4-end of MAX_PC

	pcb->IO_2_TRAPS[0] = rand()%quarterMax;
	while (pcb->IO_2_TRAPS[0] == pcb->IO_1_TRAPS[0]) {//the while loops are to ensure no duplicates between the two arrays
		pcb->IO_2_TRAPS[0] = rand()%quarterMax;
	}
	pcb->IO_2_TRAPS[1] = rand()%quarterMax + quarterMax;
	while (pcb->IO_2_TRAPS[1] == pcb->IO_1_TRAPS[1]) {
		pcb->IO_2_TRAPS[1] = rand()%quarterMax + quarterMax;
	}
	pcb->IO_2_TRAPS[2] = rand()%quarterMax + 2 * quarterMax;
	while (pcb->IO_2_TRAPS[2] == pcb->IO_1_TRAPS[2]) {
		pcb->IO_2_TRAPS[2] = rand()%quarterMax + 2 * quarterMax;
	}
	pcb->IO_2_TRAPS[3] = rand()%quarterMax + 3 * quarterMax;
	while (pcb->IO_2_TRAPS[3] == pcb->IO_1_TRAPS[3]) {
		pcb->IO_2_TRAPS[3] = rand()%quarterMax + 3 * quarterMax;
	}

 }


char *PCBToString(PcbPtr pcb) {
	if (pcb == NULL)
		return NULL;

	char * emptyStr = (char*) malloc(sizeof(char) * 1000);
	emptyStr[99] = '\0';
	char* stateString = StateToString(pcb->state);

	int lenNeeded = sprintf(emptyStr, "ID: %d, Priority: %d, State: %s, PC: %d, "
			"MAX_PC %d"
			", CREATION %f"
			", TERMINATE %d"
			", TERM_COUNT %d"
			"\n	IO_1_TRAPS: [%d, %d, %d, %d]"
			"\n	IO_2_TRAPS: [%d, %d, %d, %d]"
							, pcb->ID, pcb->priority, stateString, pcb->PC
							, pcb->MAX_PC
							, pcb->CREATION
							, pcb->TERMINATE
							, pcb->TERM_COUNT
							, pcb->IO_1_TRAPS[0],pcb->IO_1_TRAPS[1],pcb->IO_1_TRAPS[2],pcb->IO_1_TRAPS[3]
							, pcb->IO_2_TRAPS[0],pcb->IO_2_TRAPS[1],pcb->IO_2_TRAPS[2],pcb->IO_2_TRAPS[3]
							                                                                         );

	free(stateString);
//	int lenNeeded = sprintf(emptyStr, "ID: %d, Priority: %d, State: %d", //comment in for printing int value
//							pcb->ID, pcb->priority, pcb->state);

	/*int lenNeeded = sprintf(emptyStr, "ID: %d, Priority: %d, State: %s, PC: %d",
							pcb->ID, pcb->priority, PCBGetState(pcb), pcb->PC);*/ //Sean's
	char * retString = (char *) malloc(sizeof(char) * lenNeeded);
	sprintf(retString, "%s", emptyStr);
	free(emptyStr);
	return retString;
}

void PCBDestructor(PcbPtr pcb) {
	free (pcb);
	pcb = NULL;	//Only locally sets the pointer to null
}
