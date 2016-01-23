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


typedef struct PCB {
	int priority;
	int ID;
	struct PCB * next;
} PcbStr;


typedef PcbStr * PcbPtr;

/**
 * Sets a new priority for this PCB.
 */
void setPriority(PcbPtr pcb, int priority);

/**
 * Sets a new ID for this PCB.
 */
void setID(PcbPtr pcb, int id);

/**
 * Sets a new Next value for this PCB.
 */
void setNext(PcbPtr pcb, PcbPtr next);

/**
 * Returns the value of the priority for this PCB.
 */
int getPriority(PcbPtr pcb);

/**
 * Returns the value of the ID for this PCB.
 */
int getID(PcbPtr pcb);

/**
 * Returns the memory location for the next PCB.
 */
PcbPtr getNext(PcbPtr pcb);

PcbPtr newPCB();

/**
 * Returns a string representation of this PCB.
 */
char *toString(PcbPtr pcb);

/**
 * Deallocates all memory references that are kept within the PCB, and then frees the PCB passed in.
 */
PcbPtr Destroy(PcbPtr pcb);

#endif /* PCB_H_ */
