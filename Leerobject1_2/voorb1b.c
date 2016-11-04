/* Source code van Voorbeeld 1B  */

#include "vxWorks.h"
#include "stdio.h"
#include "stdlib.h"
#include "posixName.h"
#include "pthread.h"
#include "sched.h"
#include "taskLib.h"
#include "logLib.h"
#include "kernelLib.h"





void* taskOne();
void* taskTwo();
void* taskThree();
void* taskFour();




#define LONG_TIME 100000

pthread_t            tid1,tid2,tid3,tid4; 
 pthread_attr_t       attr; 
 struct sched_param   AppSchedPrio;

STATUS start(void)
{  
   
 

  
   pthreadLibInit(); 

   if(kernelTimeSlice(10)!=OK) printf("\n Time slice error");
   
   if( pthread_attr_init(&attr)!=0 ) printf("\n thread attribute object init error"); 
    
    
   /* create the pthreads */ 
   if( pthread_create(&tid1, &attr,taskOne ,0)!=0)   printf("\n thread 1 create error"); 
   if( pthread_create(&tid2, &attr,taskTwo ,0 )!=0)  printf("\n thread 2 create error");
   if( pthread_create(&tid3, &attr,taskThree ,0)!=0) printf("\n thread 3 create error");
   if( pthread_create(&tid4, &attr,taskFour ,0 )!=0) printf("\n thread 4 create error");


   AppSchedPrio.sched_priority = 110;
   pthread_setschedparam(tid1,SCHED_RR,&AppSchedPrio);
   pthread_setschedparam(tid2,SCHED_RR,&AppSchedPrio);

   AppSchedPrio.sched_priority = 120;
   pthread_setschedparam(tid3,SCHED_RR,&AppSchedPrio);
   pthread_setschedparam(tid4,SCHED_RR,&AppSchedPrio);

   return (OK);
   
}




void* taskOne()
{ 

 int i,j,y,m,n;
 
 while(1)
   {
 
       for(i=0;i<5;i++)
         {   y=1; 
             for(j=1;j<=8;j++)
	      {
               logMsg("taak 1 %i\n",y,0,0,0,0,0);
               for (m=0;m<=1000;m++)
               for(n=0;n<=LONG_TIME;n++);     
               y=y*2;
	      }			
            
          }
       AppSchedPrio.sched_priority = 110;
       pthread_setschedparam(tid1,SCHED_RR,&AppSchedPrio);
       pthread_setschedparam(tid2,SCHED_RR,&AppSchedPrio);

       AppSchedPrio.sched_priority = 120;
       pthread_setschedparam(tid3,SCHED_RR,&AppSchedPrio);
       pthread_setschedparam(tid4,SCHED_RR,&AppSchedPrio);
   }
   
}





void* taskTwo()
{ 

int i,j,y,m,n;


while(1)
  {
 
      for(i=0;i<5;i++)
           { y=1; 
             for(j=1;j<=8;j++)
	      {
               logMsg("taak 2 %i\n",y,0,0,0,0,0);
               for (m=0;m<=1000;m++)
               for(n=0;n<=LONG_TIME;n++);     
               y=y*2;
	      }			
            
            }
      AppSchedPrio.sched_priority = 110;
      pthread_setschedparam(tid1,SCHED_RR,&AppSchedPrio);
      pthread_setschedparam(tid2,SCHED_RR,&AppSchedPrio);

      AppSchedPrio.sched_priority = 120;
      pthread_setschedparam(tid3,SCHED_RR,&AppSchedPrio);
      pthread_setschedparam(tid4,SCHED_RR,&AppSchedPrio);
  }


}   




void* taskThree()
{ 
	while (1){
int i,j,y,m,n;

for(i=0;i<5;i++)
           { y=1; 
             for(j=1;j<=8;j++)
	      {
               logMsg("taak 3 %i\n",y,0,0,0,0,0);
               for (m=0;m<=1000;m++)
               for(n=0;n<=LONG_TIME;n++);     
               y=y*2;
	      }			
            
            }
AppSchedPrio.sched_priority = 120;
pthread_setschedparam(tid1,SCHED_RR,&AppSchedPrio);
pthread_setschedparam(tid2,SCHED_RR,&AppSchedPrio);

AppSchedPrio.sched_priority = 110;
pthread_setschedparam(tid3,SCHED_RR,&AppSchedPrio);
pthread_setschedparam(tid4,SCHED_RR,&AppSchedPrio);
	}
 
}   


   

void* taskFour()
{ 
while(1){
int i,j,y,m,n;

for(i=0;i<5;i++)
           {
             y=1; 
             for(j=1;j<=8;j++)
	      {
               logMsg("taak 4 %i\n",y,0,0,0,0,0);
               for (m=0;m<=1000;m++)
               for(n=0;n<=LONG_TIME;n++);     
               y=y*2;
	      }			
            
            }
AppSchedPrio.sched_priority = 120;
pthread_setschedparam(tid1,SCHED_RR,&AppSchedPrio);
pthread_setschedparam(tid2,SCHED_RR,&AppSchedPrio);

AppSchedPrio.sched_priority = 110;
pthread_setschedparam(tid3,SCHED_RR,&AppSchedPrio);
pthread_setschedparam(tid4,SCHED_RR,&AppSchedPrio);
}
}






