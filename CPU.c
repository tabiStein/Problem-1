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
unsigned int sysStackPC;		// Renamed for clarity. Let me know if you have any disagreements, so that we can talk about it :)
FifoQueue* newProcesses;
FifoQueue* readyProcesses;
FifoQueue* terminatedProcesses;
PcbPtr currProcess;

/*Prepares the waiting process to be executed.*/
void dispatcher() {
	// Let me know if you think I've misinterpreted the directions (which is entirely possible) :)
	
	PCBSetPC(currProcess, sysStackPC);
	currProcess = fifoQueueDequeue(readyProcesses);
	PCBSetState(currProcess, running);
	sysStackPC = PCBGetPC(currProcess);
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
		newProc = PCBNew();
		if(newProc != NULL)	// Remember to call the destructor when finished using newProc
		{
			currPID++;
			PCBSetID(newProc, currPID);
			PCBSetPriority(newProc, rand() % PRIORITY_LEVELS);
			PCBSetState(newProc, created);
			fifoQueueEnqueue(newProcesses, newProc);
		}
	}
}

/*Writes the given string to the given file*/
void writeToFile(FILE* filePtr, char* string) {
  fprintf(filePtr, "%s", string);
}

int main(void) {
	currPID = 0;
	sysStackPC = 0;
	newProcesses = fifoQueueConstructor();
	readyProcesses = fifoQueueConstructor();
	terminatedProcesses = fifoQueueConstructor();
	currProcess = NULL;
	
	/*
	 * Fill in code here!! \(^o^)/
	 */
	
	fifoQueueDestructor(newProcesses);
	fifoQueueDestructor(readyProcesses);
	fifoQueueDestructor(terminatedProcesses);
	PCBDestroy(currProcess);
	printf("Done\n");
	return 0;
}
