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
void task1(int a, int b, int c);

#define TIMESLICE sysClkRateGet()
#define LONG_TIME 100000
#define MY_INUM1 0x200  // Met de Sendmessage tool 0x8200 versturen!
#define MY_INUM2 0x201  // Met de Sendmessage tool 0x8201 versturen!

int taskIdOne;
void taskOne(void);

int n;
void start()
{

 if(kernelTimeSlice(10)==OK) printf("goed\n");

 taskIdOne=taskSpawn("t1",80,0x100,10000,(FUNCPTR)taskOne,0,0,0,0,0,0,0,0,0,0);
 

 if (intConnect((VOIDFUNCPTR *)INUM_TO_IVEC(MY_INUM1),
  (VOIDFUNCPTR) interruptHandler1,0) != OK)  printf("error");



}




void taskOne()
{

  while(1){
	   n=n++; // wait for interrupt
  }

}




void interruptHandler1(int arg)
{   
 task1(1,2,3);
}

void task1(int a, int b, int c){
	printf("number on %d number 2 %d number 3 %d",a,b,c);
}
