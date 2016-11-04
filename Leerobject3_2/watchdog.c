/* Source code van Voorbeeld 1A */

#include "vxWorks.h"
#include "stdio.h"
#include "stdlib.h"
#include "taskLib.h"
#include "sysLib.h"
#include "logLib.h"
#include "kernelLib.h"


void taskOne(void);
void taskTwo(void);
void watchdog(void);





#define TIMESLICE sysClkRateGet()

int taskIdOne,taskIdTwo,taskIdThree;
int flagTaskOne, flagTaskTwo;
STATUS start(void)
{
   if(kernelTimeSlice(10)!=OK) printf("Time slice error");
   flagTaskOne=0;
   flagTaskTwo=0;
   if( (taskIdOne=taskSpawn("t1",100,0x100,2000,(FUNCPTR)taskOne,0,0,0,0,0,0,0,0,0,0) ) ==ERROR)    printf("taskspawn taak 1 error");
   if( (taskIdTwo=taskSpawn("t2",100,0x100,2000,(FUNCPTR)taskTwo,0,0,0,0,0,0,0,0,0,0) ) ==ERROR)    printf("taskspawn taak 2 error"); 
   if( (taskIdThree=taskSpawn("t2",110,0x100,2000,(FUNCPTR)watchdog,0,0,0,0,0,0,0,0,0,0) ) ==ERROR)    printf("taskspawn taak 2 error"); 
   return (OK);

}



void taskOne(void)
{ 


 
 while(1)
   {
	 flagTaskOne=1;
    
printf("executing task1 \n");
taskDelay(150);
    }

}





void taskTwo(void)
{ 


 
while(1)
  {
	flagTaskTwo=1;
	printf("executing task2\n");
	taskDelay(250);
  }
}   
void watchdog(void){
	while(1){
		taskDelay(350);
		int check1=0;
		int check2=0;
		if (flagTaskOne==1){
			check1=1;
		}
		if (flagTaskTwo==1){
				check2=1;
			}
		if(check1==1&&check2==1){
			printf("Alive and well\n");
		}
		else{
			printf("died");
		}
		flagTaskOne=0;
		flagTaskTwo=0;
	}
}






void stop (void)
{
    taskDelete (taskIdOne);
    taskDelete (taskIdTwo);


    return; 
}
