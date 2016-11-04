/* Source code van Voorbeeld 1*/

#include "vxWorks.h"
#include "stdio.h"
#include "stdlib.h"
#include "taskLib.h"
#include "sysLib.h"
#include "logLib.h"
#include "kernelLib.h"
#include "semLib.h"

#define TIMESLICE sysClkRateGet()/4




void taskOne(void);
void taskTwo(void);
void taskThree(void);
SEM_ID semBinary;
int global=0;




STATUS start(void)
{

  int taskIdOne,taskIdTwo,taskIdThree;
  if(kernelTimeSlice(10)!=OK) printf("Time slice error");

  semBinary=semMCreate(SEM_Q_PRIORITY|SEM_INVERSION_SAFE);

  if( (taskIdOne=taskSpawn("t1",10,0x100,2000,(FUNCPTR)taskOne,0,0,0,0,0,0,0,0,0,0) ) ==ERROR)    printf("taskspawn taak 1 error");
  if( (taskIdTwo=taskSpawn("t2",20,0x100,2000,(FUNCPTR)taskTwo,0,0,0,0,0,0,0,0,0,0) ) ==ERROR)     printf("taskspawn taak 2 error"); 
  if( (taskIdThree=taskSpawn("t3",110,0x100,2000,(FUNCPTR)taskThree,0,0,0,0,0,0,0,0,0,0) ) ==ERROR)     printf("taskspawn taak 3 error"); 
  return (OK);
 
}



void taskOne(void)
{ int j;
  while(1)
   {
    semTake(semBinary,WAIT_FOREVER);
        for(j=0;j<20;j++){
            printf("I am task one and global = %d....\n",++global);
            taskDelay(TIMESLICE);
            }
    semGive(semBinary);
    }        

}   





void taskTwo(void)
{ int i;

  while(1)
  {
    semTake(semBinary,WAIT_FOREVER);
         for(i=0;i<20;i++)
           {
            printf("I am task two and global = %d....\n",--global);
            taskDelay(TIMESLICE);
            }
    semGive(semBinary);
    
   }
}   
void taskThree(void)
{ int i;

  while(1)
  {
    semTake(semBinary,WAIT_FOREVER);
         for(i=0;i<100;i++)
           {
            printf("I am task three and global = %d....\n",--global);
            taskDelay(TIMESLICE);
            }
    semGive(semBinary);
    
   }
}   




void stop (void)
{
    //taskDelete (taskIdOne);
    //taskDelete (taskIdTwo);
    //taskDelete (taskIdThree);
   // taskDelete (taskIdFour);

	semDelete (semBinary);

    return; 
}
      
