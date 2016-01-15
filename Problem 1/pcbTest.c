///*	pcbTest
// * 	Author: Tabi Stein
// */
//
//
//#include "Pcb.h"
//
//#include <stdlib.h>
//#include <stdio.h>
//#include <time.h>
//

//Abby's updated test
int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	//PcbStr *randPcb = malloc(sizeof(PcbStr));
	PcbStr *randPcb = newPCB();
	printf("PCB Before defining members:\n %s\n", toString(randPcb));
	srand( time(NULL) );
	setPriority(randPcb, rand() % 16);
	setID(randPcb, rand());
	printf("Press enter to see PCB after members have been randomly defined:\n");
	getchar();
	printf("%s\n", toString(randPcb));
	return 0;
}

//int main(void) {
//	setvbuf(stdout, NULL, _IONBF, 0);
//	PcbStr *randPcb = malloc(sizeof(PcbStr));
//	printf("PCB Before defining members:\n %s\n", toString(randPcb));
//	srand( time(NULL) );
//	setPriority(randPcb, rand() % 32);
//	setID(randPcb, rand());
//	printf("Press enter to see PCB after members have been randomly defined:\n");
//	getchar();
//	printf("%s\n", toString(randPcb));
//	return 0;
//}
