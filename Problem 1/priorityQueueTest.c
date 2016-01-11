#include <stdbool.h>
#include <string.h>

#include "PriorityQueue.h"
#include "Fifo.h"
#include "Pcb.h"


int main() {
    PQPtr pQ = pqConstructor();

    //create 10 pcbs with a random priority, ids from 1-10?
    //enqueue each pcb, print as they are enqueued
    srand( time(NULL) );
    PcbPtr pcb;
    int i;
    for (i = 0; i < 10; i++) {
        //printf("%s\n", pqToString(pQ));
        //printf("%d\n", i);
        pcb = newPCB();
        setPriority(pcb, rand() % 15);

        printf("%d\n", pcb->priority);

        setID(pcb, i + 1);
        pqEnqueue(pQ, pcb);
        //print out the priority queue so far
        printf("%s\n", pqToString(pQ));
    }
    return 0;
}

