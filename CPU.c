#include pcb.h
#include FIFO.h
#define TIMER 1

int sysStack;
FIFO newProcesses;
FIFO readyProcesses;
FIFO terminatedProcesses;
PCB currProcesses;

/*Prepares the waiting process to be executed.*/
void dispatcher() {
}

/*Based on the type of interrupt indicated,
  decides what to do with the current process.*/
void scheduler(int interruptType) {
}

/*The interrupt service routine for a timer interrupt.*/
void timerIsr() {
}

/*Randomly generates between 0 and 5 new processes*/
void newProcesses() {
}

/*Writes the given string to the given file*/
void writeToFile(FILE* filePtr, char* string) {
  fprintf(filePtr, "%s", string);
}

int main(void) {
  return 0;
}

