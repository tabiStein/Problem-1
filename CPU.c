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
#define IO_INTERRUPT 3
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
	} else if (interruptType == TERMINATE_INTERUPT) {
		fifoQueueEnqueue(terminatedProcesses, currProcess);
		PCBSetState(currProcess, terminated);
		currProcess->TERMINATION = (double)clock();
		dispatcher();
	}
}

/*Saves the state of the CPU to the currently running PCB.*/
void saveCpuToPcb() {
	PCBSetPC(currProcess, sysStackPC);
}

void terminateIsr() {
	//save cpu to pcb??
	PCBSetState(currProcess, interrupted);
	scheduler(TERMINATE_INTERRUPT, -1);
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

int main(void) {
	srand(time(NULL));
	outFilePtr = fopen("scheduleTrace.txt", "w");
	currPID = 0;
	sysStackPC = 0;
	io1Count = -1;
	io2Count = -1;
	timerCount = TIMER_QUANTUM;
	//unsigned int PCRegister;
	newProcesses = fifoQueueConstructor();
	readyProcesses = fifoQueueConstructor();
	terminatedProcesses = fifoQueueConstructor();
	waitQueue1 = fifoQueueConstructor();
	waitQueue2 = fifoQueueConstructor();

	/*
	//An initial process to start with
	currProcess = PCBConstructor();
	PCBSetPC(currProcess, rand());
	PCBSetID(currProcess, currPID);
	PCBSetPriority(currProcess, rand() % PRIORITY_LEVELS);
	PCBSetState(currProcess, running);
	currPID++;
	//PCRegister = currProcess->PC;

	 */

	printf("Generating Processes:\n");

	genProcesses();
	int i;
	for (i = 0; i < newProcesses->size; i++) {
		PcbPtr pcb = fifoQueueDequeue(newProcesses);
		PCBSetState(pcb, ready);
		fifoQueueEnqueue(readyProcesses, pcb);
		//fprintf(outFilePtr, "%s\r\n", PCBToString(pcb));
	}
	dispatcher();

	printf("Begin Simulation:\n");
	printf("Currently running process: %s\n\n", PCBToString(currProcess));

	int simCounter = 0;
	while (simCounter <= SIMULATION_END) {
		//check for timer interrupt, if so, call timerISR()
		if (timerCheck() == 1) {
			printf("A timer interrupt has occurred.\n");

			timerIsr();

			printf("readyProcesses current state: %s\n", fifoQueueToString(readyProcesses));
			printf("Currently running process: %s\n\n", PCBToString(currProcess));
		}

		//check if there has been an IO interrupt, if so call appropriate ioISR
		if (io1Check() == 1) {
			printf("I/O 1 device has thrown an interrupt.\n");

			//call the IO service routine
			IO_ISR(1);

			printf("waitQueue1 current state: %s\n\n", fifoQueueToString(waitQueue1));
		}
		if (io2Check() == 1) {
			printf("I/O 2 device has thrown an interrupt.\n");

			//call the IO service routine
			IO_ISR(2);

			printf("waitQueue2 current state: %s\n\n", fifoQueueToString(waitQueue2));
		}

		//check the current process's PC, if it is MAX_PC, set to 0 and increment TERM_COUNT
		if (currProcess->PC == currProcess->MAX_PC) {
			currProcess->TERM_COUNT++;

			//if TERM_COUNT = TERMINATE, then call terminateISR to put this process in the terminated list
			if (currProcess->TERM_COUNT == currProcess->TERMINATE) {
				printf("process being terminated\n");

				terminateIsr();

				printf("Terminated process: %s\n", PCBToString(currProcess));
				printf("terminatedProcesses current state: %s\n", fifoQueueToString(terminatedProcesses));
				printf("readyProcesses current state: %s\n", fifoQueueToString(readyProcesses));
				printf("Currently running process: %s\n\n", PCBToString(currProcess));

				continue;	//currProcess has been terminated, we don't want to execute the rest of the loop, instead jump to next iteration
			}
			currProcess->PC = 0;
		}

		//increment the current process's PC
		currProcess->PC++;

		//check the current process's PC to see if it's an I/O, if so, call ioISR on appropriate I/O device
		if (currProcess->PC == currProcess->IO_1_TRAPS[0] ||
				currProcess->PC == currProcess->IO_1_TRAPS[1] ||
				currProcess->PC == currProcess->IO_1_TRAPS[2] ||
				currProcess->PC == currProcess->IO_1_TRAPS[3]) {

			printf("I/O 1 request\n");

			trapServiceHandler(1);

			printf("waitQueue1 current state: %s\n", fifoQueueToString(waitQueue1));
			printf("Currently running process: %s\n\n", PCBToString(currProcess));
		} else if (currProcess->PC == currProcess->IO_2_TRAPS[0] ||
				currProcess->PC == currProcess->IO_2_TRAPS[1] ||
				currProcess->PC == currProcess->IO_2_TRAPS[2] ||
				currProcess->PC == currProcess->IO_2_TRAPS[3]) {

			printf("I/O 2 request\n");

			trapServiceHandler(2);

			printf("waitQueue2 current state: %s\n", fifoQueueToString(waitQueue2));
			printf("Currently running process: %s\n\n", PCBToString(currProcess));
		}

		//at end
		simCounter++;
	}

	printf("End of simulation\n");
	return 0;
}



//Writes the given string to the given file
//void writeToFile(FILE* filePtr, const char* string) {
//  fprintf(filePtr, "%s", string);
//}

/*
int main(void) {
	srand(time(NULL));
	outFilePtr = fopen("scheduleTrace.txt", "w");
	currPID = 0;
	sysStackPC = 0;
	newProcesses = fifoQueueConstructor();
	readyProcesses = fifoQueueConstructor();
	terminatedProcesses = fifoQueueConstructor();
	unsigned int PCRegister;

	//An initial process to start with
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
*/
