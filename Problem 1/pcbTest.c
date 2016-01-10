/*	pcbTest
 * 	Author: Tabi Stein
 */


#include "pcb.h"

#include <stdlib.h>
#include <stdio.h>

	int main(void) {
		pcbPtr randPcb = (pcbPtr) malloc(pcbSize());
		printf("%s\n", toString(randPcb));
		setPriority(randPcb, rand() % 32);
		setID(randPcb, rand());
		printf("%s\n", toString(randPcb));
	}
