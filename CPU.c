/***********************************************************************************************
* CPU.c
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
* This C file implements the class and methods for the CPU.
*
************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Pcb.h"
#include "Fifo.h"

#define TIMER 1
#define NEW_PROCS 5
#define PRIORITY_LEVELS 16

int currPID;
int sysStackPC;		// Renamed for clarity. Let me know if you have any disagreements, so that we can talk about it :)
fQ* newProcesses;
fQ* readyProcesses;
fQ* terminatedProcesses;
PcbPtr currProcess;

/*Prepares the waiting process to be executed.*/
void dispatcher() {
	// Let me know if you think I've misinterpreted the directions (which is entirely possible) :)
	
	// pcb_setPC(currProcess, sysStackPC);							// TO BE IMPLEMENTED
	currProcess = fifoDequeue(readyProcesses);
	// pcb_setState(currProcess, RUNNING);							// TO BE IMPLEMENTED
	// sysStackPC = pcb_getPC(currProcess);							// TO BE IMPLEMENTED
}

/*Based on the type of interrupt indicated,
  decides what to do with the current process.*/
void scheduler(int interruptType) {
}

/*The interrupt service routine for a timer interrupt.*/
void timerIsr() {
}

/*Randomly generates between 0 and 5 new processes and enqueues them to the New Processes Queue.*/
void genProcesses() {
	srand(time(NULL));
	PcbPtr newProc;
	
	int i;
	// rand() % NEW_PROCS will range from 0 to NEW_PROCS - 1, so we must use rand() % (NEW_PROCS + 1)
	for(i = 0; i < rand() % (NEW_PROCS + 1); i++)
	{
		newProc = newPCB();
		if(newProc != NULL)	// Remember to call the destructor when finished using newProc
		{
			currPID++;
			setID(newProc, currPID);
			setPriority(newProc, rand() % PRIORITY_LEVELS);
			//pcb_setState(newProc, CREATED);						// TO BE IMPLEMENTED
			fifoEnqueue(newProcesses, newProc);
		}
	}
}

/*Writes the given string to the given file*/
void writeToFile(FILE* filePtr, char* string) {
  fprintf(filePtr, "%s", string);
}

int main(void) {
	newProcesses = createfQ();
	readyProcesses = createfQ();
	terminatedProcesses = createfQ();
	currPID = 0;
	
	/*
	 * Fill in code here!! \(^o^)/
	 */
	
	fQDestructor(newProcesses);
	fQDestructor(readyProcesses);
	fQDestructor(terminatedProcesses);
	return 0;
}

