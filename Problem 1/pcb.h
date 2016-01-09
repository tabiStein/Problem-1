/*
 * pcb.h
 *
 *  Created on: Jan 7, 2016
 *      Author: Sean
 *      Contributor: Abigail
 */

#ifndef PCB_H_
#define PCB_H_

typedef struct pcb {
	int priority;
	int ID;
	int next;
} PCB;
typedef PCB * PCB_p;

/**
 * Sets a new priority for this PCB
 */
void setPriority(int * priority);

/**
 * Returns the value of the priority of this PCB
 */
int getPriority();

/**
 * Returns a string representation of this PCB.
 */
const char *toString();

/**
 * Deallocates all memory references that are kept within this PCB.
 */
void Destroy();

#endif /* PCB_H_ */
