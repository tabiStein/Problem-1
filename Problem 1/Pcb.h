/*
 * pcb.h
 *
 *  Created on: Jan 7, 2016
 *      Author: Sean
 *      Author: Abigail
 */

#ifndef PCB_H_
#define PCB_H_

typedef struct pcb {
	int priority;
	int ID;
	int * next;
} PCB;
typedef PCB * PCB_p;

/**
 * Sets a new priority for this PCB.
 */
void setPriority(PCB * pcb, int * priority);

/**
 * Sets a new ID for this PCB.
 */
void setID(PCB * pcb, int * id);

/**
 * Sets a new Next value for this PCB.
 */
void setNext(PCB * pcb, int * next);

/**
 * Returns the value of the priority for this PCB.
 */
int getPriority();

/**
 * Returns the value of the ID for this PCB.
 */
int getID();

/**
 * Returns the memory location for the next PCB.
 */
int *getNext();

/**
 * Returns a string representation of this PCB.
 */
const char *toString(PCB * pcb);

/**
 * Deallocates all memory references that are kept within the PCB, and then frees the PCB passed in.
 */
int *Destroy(PCB * pcb);

#endif /* PCB_H_ */
