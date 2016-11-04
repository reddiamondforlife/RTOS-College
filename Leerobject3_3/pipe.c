/* Source code van Voorbeeld 1*/

#include "vxWorks.h"
#include "stdio.h"
#include "stdlib.h"
#include "taskLib.h"
#include "sysLib.h"
#include "logLib.h"
#include "kernelLib.h"
#include "semLib.h"
#include "ioLib.h"
#include "pipeDrv.h"
#define TIMESLICE sysClkRateGet()/4




void taskOne(void);
void taskTwo(void);






STATUS start(void)
{

  int taskIdOne,taskIdTwo;
  if(kernelTimeSlice(10)!=OK) printf("Time slice error");


  if( (taskIdOne=taskSpawn("t1",10,0x100,2000,(FUNCPTR)taskOne,0,0,0,0,0,0,0,0,0,0) ) ==ERROR)    printf("taskspawn taak 1 error");
  if( (taskIdTwo=taskSpawn("t2",10,0x100,2000,(FUNCPTR)taskTwo,0,0,0,0,0,0,0,0,0,0) ) ==ERROR)     printf("taskspawn taak 2 error"); 
  return (OK);
  pipeDevCreate ("/pipe/demo", 10, 100);
 
}



void taskOne(void)
{ 
  while(1)
   {
	  
	  	 int fd;
	     int outMsg;
	     int len;
	     fd = open ("/pipe/demo", O_WRONLY,0777);
	     for(outMsg=0;outMsg<50;outMsg++){
	     write (fd, &outMsg, sizeof (int));
	     printf("message : sent %d \n",outMsg);
	     }
	     close (fd);
 
    }        

}   





void taskTwo(void)
{

  while(1)
  {	 		int fd;
	     	 int inMsg;
	     	 int outMsg;
	  	  	 int len;
	  	     fd = open ("/pipe/demo", O_RDONLY,0777);
	  	     len = read (fd, &inMsg, sizeof (int));
	  	     if(len==0){
	  	     printf("Message received : %d \n", inMsg);
	  	     }
	  	   
	  	     close (fd);
    
   }
}   




void stop (void)
{
    //taskDelete (taskIdOne);
    //taskDelete (taskIdTwo);
    //taskDelete (taskIdThree);
   // taskDelete (taskIdFour);

    return; 
}
      
