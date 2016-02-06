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
#define IO 2
#define IOTRAP 3
#define NEW_PROCS 5
#define PRIORITY_LEVELS 16
#define ROUNDS_TO_PRINT 4 // the number of rounds to wait before printing simulation data
#define SIMULATION_END 30 //the minimum number of processes before the simulation may end
#define MIN_PC_INCREMENT 3000
#define PC_INCREMENT_RANGE 1000


//Global variables
int currPID; //The number of processes created so far. The latest process has this as its ID.
unsigned int sysStackPC;
FifoQueue* wait_queue1;
FifoQueue* wait_queue2;
FifoQueue* newProcesses;
FifoQueue* readyProcesses;
FifoQueue* terminatedProcesses;
PcbPtr currProcess;
FILE* outFilePtr;

/*Prepares the waiting process to be executed.*/
void dispatcher() {
	currProcess = fifoQueueDequeue(readyProcesses);
	PCBSetState(currProcess, running);
	sysStackPC = PCBGetPC(currProcess);
}

/*Based on the type of interrupt indicated,
  decides what to do with the current process.*/
void scheduler(int interruptType, int numIO) {
	if (interruptType == TIMER) {
		//Get new processes into ready queue
		int i;
		for (i = 0; i < newProcesses->size; i++) {
			PcbPtr pcb = fifoQueueDequeue(newProcesses);
			PCBSetState(pcb, ready);
			fifoQueueEnqueue(readyProcesses, pcb);
			fprintf(outFilePtr, "%s\r\n", PCBToString(pcb));
		}
		fifoQueueEnqueue(readyProcesses, currProcess);
		PCBSetState(currProcess, ready);
		dispatcher();
	}

	else if (interruptType == IO) {
		//Get process from waiting queue
		PcbPtr pcb;
		if (numIO == 1) {
			pcb = fifoQueueDequeue(wait_queue1);
		}
		else if (numIO == 2) {
			pcb = fifoQueueDequeue(wait_queue2);
		}
		//put current process into ready queue
		fifoQueueEnqueue(readyProcesses, currProcess);
		PCBSetState(currProcess, ready);
		//set new io waiting queue process to running
		currProcess = pcb;
		PCBSetState(currProcess, running);
	}
	else if (interruptType == IOTRAP) {
		//Put process into waiting queue
		if (numIO == 1) {
			fifoQueueEnqueue(wait_queue1, currProcess);
		}
		else if (numIO == 2) {
			fifoQueueEnqueue(wait_queue2, currProcess);
		}
		//set new io waiting queue process to running
		dispatcher();
	}
}

/*Saves the state of the CPU to the currently running PCB.*/
void saveCpuToPcb() {
	PCBSetPC(currProcess, sysStackPC);
}

/*The interrupt service routine for a IO interrupt
 * Does it still have to save Cpu state to Pcb? */
void IO_ISR(int numIO) {
	saveCpuToPcb();
	PCBSetState(currProcess, interrupted);
	scheduler(IO, numIO);
}

/*The interrupt service routine for a timer interrupt.*/
void timerIsr() {
	saveCpuToPcb();
	PCBSetState(currProcess, interrupted);
	scheduler(TIMER, NULL);
}

/**
 * Checks the trap array if PC value matches
 * returns I/O 1 or I/O 2 if match 0 otherwise
 */
int trap_check(int CPU, PcbPtr *pcb) {
	int i;
	for (i = 0; i < 4; i++)  {
		//When I/O cycle number % CPU == 0
		if (pcb->IO_1_TRAPS[i] % CPU == 0) {
			return 1;
		}
		if (pcb->IO_1_TRAPS[i] % CPU == 0) {
			return 2;
		}
	}
	return 0;
}

/**
 * Puts running pcb into blocked state and into IO queue, calls scheduler
 */
void trap_service_handler(int numIO) {
	saveCpuToPcb();
		PCBSetState(currProcess, blocked);
		scheduler(IOTRAP, NULL);
		//TURN ON/ALERT IO CHECK THREAD HERE TO BEGIN COUNTDOWN
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

///*Writes the given string to the given file*/
//void writeToFile(FILE* filePtr, const char* string) {
//  fprintf(filePtr, "%s", string);
//}

int main(void) {
	srand(time(NULL));
	outFilePtr = fopen("scheduleTrace.txt", "w");
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
	
	fprintf(outFilePtr, "%s", "Sean Markus\r\nWing-Sea Poon\r\nAbigail Smith\r\nTabi Stein\r\n\r\n");

	int numContextSwitches = 0;
	while (currPID <= SIMULATION_END) {
		genProcesses();
		PCRegister += (rand() % PC_INCREMENT_RANGE) + MIN_PC_INCREMENT;
		sysStackPC = PCRegister;
		PcbPtr extraRef = currProcess;

		if (numContextSwitches % ROUNDS_TO_PRINT == 0) {
			printf("Number of PCBs dispatched so far: %d\r\n", numContextSwitches); //test
			printf("Running PCB: %s\r\n", PCBToString(currProcess));
			fprintf(outFilePtr, "Number of PCBs dispatched so far: %d\r\n", numContextSwitches);
			fprintf(outFilePtr, "Running PCB: %s\r\n", PCBToString(currProcess));

			if (fifoQueuePeek(readyProcesses) != NULL) {
				printf("Switching to: %s\r\n", PCBToString(fifoQueuePeek(readyProcesses)));
				fprintf(outFilePtr, "Switching to: %s\r\n", PCBToString(fifoQueuePeek(readyProcesses))); //Print head of readyProcesses
			}
		}
		timerIsr();
		if (numContextSwitches % ROUNDS_TO_PRINT == 0) {
			printf("After ISR: %s\r\n", PCBToString(extraRef));
			printf("Now running PCB: %s\r\n", PCBToString(currProcess));
			printf("Ready Queue: %s\r\n", fifoQueueToString(readyProcesses));
			printf("Num processes created so far: %d\r\n\r\n", currPID);
			//tofile
			fprintf(outFilePtr, "After ISR: %s\r\n", PCBToString(extraRef));
			fprintf(outFilePtr, "Now running PCB: %s\r\n", PCBToString(currProcess));
			fprintf(outFilePtr, "Ready Queue: %s\r\n", fifoQueueToString(readyProcesses));
			fprintf(outFilePtr, "Num processes created so far: %d\r\n\r\n", currPID);
		}

		PCRegister = sysStackPC;
		numContextSwitches++;
	}

	fifoQueueDestructor(&newProcesses);
	fifoQueueDestructor(&readyProcesses);
	fifoQueueDestructor(&terminatedProcesses);
	PCBDestructor(currProcess);
	fclose(outFilePtr);
	printf("Done\r\n");
	return 0;
}
