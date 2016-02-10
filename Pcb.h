/***********************************************************************************************
* Pcb.h
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
* This header file defines the class and methods for the process control block implementation.
*
************************************************************************************************/

#ifndef PCB_H_
#define PCB_H_

#define NUM_IO_TRAPS 4

typedef enum {
	created=0,
	running=1,
	ready=2,
	interrupted=3,
	blocked=4,
	terminated=5
} State;


typedef struct PCB* PcbPtr;

unsigned int get_IO_1_Trap(PcbPtr pcb, int index);
unsigned int get_IO_2_Trap(PcbPtr pcb, int index);

/*Returns a string value for the given state.*/
char* StateToString(State state);

/**
 * Sets a new priority for this PCB.
 */
void PCBSetPriority(PcbPtr pcb, int priority);

/**
 * Sets a new ID for this PCB.
 */
void PCBSetID(PcbPtr pcb, int id);

/**
 * Sets the state for this PCB.
 */
void PCBSetState(PcbPtr pcb, State newState);

/**
 * Sets the PC for this PCB.
 */
void PCBSetPC(PcbPtr pcb, unsigned int newPC);

/**
 * Returns PC of this PCB.
 */
unsigned int PCBGetPC(PcbPtr pcb);

/**
 * Returns the value of the priority for this PCB.
 */
int PCBGetPriority(PcbPtr pcb);

/**
 * Returns the value of the ID for this PCB.
 */
int PCBGetID(PcbPtr pcb);

/**
 * Returns the state of this PCB.
 */
State PCBGetState(PcbPtr pcb);

PcbPtr PCBConstructor();

/**
 * Returns a string representation of this PCB.
 */
char *PCBToString(PcbPtr pcb);

/**
 * Deallocates all memory references that are kept within the PCB, and then frees the PCB passed in.
 */
void PCBDestructor(PcbPtr pcb);

#endif /* PCB_H_ */
