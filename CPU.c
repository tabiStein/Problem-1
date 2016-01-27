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
#define SIMULATION_END 30 //the minimum number of processes before the simulation may end
#define MIN_PC_INCREMENT 3000
#define PC_INCREMENT_RANGE 1000

int currPID; //The number of processes created so far. The latest process has this as its ID.
unsigned int sysStackPC;
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
	if (interruptType == TIMER) {
		fifoQueueEnqueue(readyProcesses, currProcess);
		PCBSetState(currProcess, ready);
		dispatcher();
	}
}

/*The interrupt service routine for a timer interrupt.*/
void timerIsr() {
	PCBSetState(currProcess, interrupted);
	PCBSetPC(currProcess, sysStackPC); //Or to do in dispatcher?
	scheduler(TIMER);
}

/*Randomly generates between 0 and 5 new processes and enqueues them to the New Processes Queue.*/
void genProcesses() {

	PcbPtr newProc;

	int i;
	// rand() % NEW_PROCS will range from 0 to NEW_PROCS - 1, so we must use rand() % (NEW_PROCS + 1)
	for(i = 0; i < rand() % (NEW_PROCS + 1); i++)
	{
		newProc = PCBConstructor();
		if(newProc != NULL)	// Remember to call the destructor when finished using newProc
		{
			currPID++;
			PCBSetPC(newProc, rand());
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
	srand(time(NULL));
	currPID = 0;
	sysStackPC = 0;
	newProcesses = fifoQueueConstructor();
	readyProcesses = fifoQueueConstructor();
	terminatedProcesses = fifoQueueConstructor();
	unsigned int PCRegister;

	/*An initial process to start with*/
	currProcess = PCBConstructor();
	PCBSetPC(currProcess, rand());
	PCBSetID(currProcess, currPID);
	PCBSetPriority(currProcess, rand() % PRIORITY_LEVELS);
	PCBSetState(currProcess, running);
	currPID++;
	PCRegister = currProcess->PC;

	while (currPID <= SIMULATION_END) {
		genProcesses();
		PCRegister += (rand() % PC_INCREMENT_RANGE) + MIN_PC_INCREMENT;
		sysStackPC = PCRegister;
		PcbPtr extraRef = currProcess;
		if (currPID % 4 == 0) {
			printf("Running PCB: %s\n", PCBToString(currProcess));
			printf("Switching to: %s\n", PCBToString(fifoQueuePeek(readyProcesses))); //Print head of readyProcesses
		}
		timerIsr();
		if (currPID % 4 == 0) {
			printf("After ISR:\n%s\n", PCBToString(extraRef));
			printf("%s\n", PCBToString(currProcess));
			printf("%s\n", fifoQueueToString(readyProcesses));
		}
		PCRegister = sysStackPC;
	}

	fifoQueueDestructor(&newProcesses);
	fifoQueueDestructor(&readyProcesses);
	fifoQueueDestructor(&terminatedProcesses);
	PCBDestructor(currProcess);
	printf("Done\n");
	return 0;
}
