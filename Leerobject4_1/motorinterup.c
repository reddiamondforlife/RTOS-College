/* Source code van Voorbeeld 3 */

#include "vxWorks.h"
#include "stdio.h"
#include "stdlib.h"
#include "taskLib.h"
#include "sysLib.h"
#include "logLib.h"
#include "kernelLib.h"
#include "intLib.h"
#include "iv.h"
#include "fioLib.h"





void interruptHandler1(int arg);
void interruptHandler2(int arg);
void interruptHandler3(int arg);

#define TIMESLICE sysClkRateGet()
#define LONG_TIME 100000
#define MY_INUM1 0x200  // Met de Sendmessage tool 0x8200 versturen!
#define MY_INUM2 0x201  // Met de Sendmessage tool 0x8201 versturen!
#define MY_INUM3 0x202  // Met de Sendmessage tool 0x8202 versturen!
int taskIdOne;
int taskIdTwo;
void taskOne(void);
#define TIMESLICE sysClkRateGet()

void start()
{

 if(kernelTimeSlice(10)==OK) printf("goed\n");

 taskIdOne=taskSpawn("t1",80,0x100,10000,(FUNCPTR)taskOne,0,0,0,0,0,0,0,0,0,0);
 

 if (intConnect((VOIDFUNCPTR *)INUM_TO_IVEC(MY_INUM1),
  (VOIDFUNCPTR) interruptHandler1, 0) != OK)  printf("error");

 if (intConnect((VOIDFUNCPTR *)INUM_TO_IVEC(MY_INUM2),
  (VOIDFUNCPTR) interruptHandler2, 0) != OK)  printf("error");
 if (intConnect((VOIDFUNCPTR *)INUM_TO_IVEC(MY_INUM3),
  (VOIDFUNCPTR) interruptHandler3, 0) != OK)  printf("error");

}




void taskOne()
{

  while(1); // wait for interrupt

}

void motorTwoAndThree(){
	printf("running motor 2 and 3");
taskDelay(TIMESLICE*6.4);	
}

void motorOne(){
	printf("running motor 1 ");
	taskDelay(TIMESLICE*3.5);
	motorTwoAndThree();
}



void interruptHandler1(int arg)
{   
	 taskIdTwo=taskSpawn("t1",80,0x100,10000,(FUNCPTR)motorOne,0,0,0,0,0,0,0,0,0,0);
}


void interruptHandler2(int arg)
{   
	taskSuspend(taskIdTwo);
	intDisable(MY_INUM1); 
}
void interruptHandler3(int arg){
	taskSuspend(taskIdTwo);
	intDisable(MY_INUM1); 
}
