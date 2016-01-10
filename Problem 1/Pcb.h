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
	struct PCB * next;
} PCB;


typedef struct PCB * PCB_p;

/**
 * Sets a new priority for this PCB.
 */
void setPriority(PCB_p pcb, int * priority);

/**
 * Sets a new ID for this PCB.
 */
void setID(PCB_p pcb, int * id);

/**
 * Sets a new Next value for this PCB.
 */
void setNext(PCB_p pcb, struct PCB * next);

/**
 * Returns the value of the priority for this PCB.
 */
int getPriority(PCB_p pcb);

/**
 * Returns the value of the ID for this PCB.
 */
int getID(PCB_p pcb);

/**
 * Returns the memory location for the next PCB.
 */
struct PCB *getNext(PCB_p pcb);

struct PCB *newPCB();

/**
 * Returns a string representation of this PCB.
 */
const char *toString(PCB_p pcb);

/**
 * Deallocates all memory references that are kept within the PCB, and then frees the PCB passed in.
 */
int *Destroy(PCB_p pcb);

#endif /* PCB_H_ */
