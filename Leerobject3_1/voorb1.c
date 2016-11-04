/* Source code van Voorbeeld 1 */

#include "vxWorks.h"
#include "stdio.h"
#include "stdlib.h"
#include "semLib.h"
#include "taskLib.h"
#include "sysLib.h"
#include "msgQLib.h" 
#include "posixName.h"
#include "pthread.h"
#include "sched.h"
 
#define MAX_MSGS (10)
#define MAX_MSG_LEN (100) 
#define MESSAGE "Greetings from Task 1" 


void receiveTask(void);
void sendTask(void);
pthread_t            tid1,tid2;
pthread_attr_t       attr; 
struct sched_param   AppSchedPrio;
MSG_Q_ID myMsgQ; 


void start()
{


pthreadLibInit(); 

if(kernelTimeSlice(10)!=OK) printf("\n Time slice error");

if( pthread_attr_init(&attr)!=0 ) printf("\n thread attribute object init error"); 


if( pthread_create(&tid1, &attr,receiveTask ,0)!=0)   printf("\n thread 1 create error"); 
  if( pthread_create(&tid2, &attr,sendTask ,0 )!=0)  printf("\n thread 2 create error");
  
  AppSchedPrio.sched_priority = 80;
 pthread_setschedparam(tid1,SCHED_RR,&AppSchedPrio);
 AppSchedPrio.sched_priority = 90;
  pthread_setschedparam(tid2,SCHED_RR,&AppSchedPrio);



/* create message queue */ 
if ((myMsgQ= msgQCreate (MAX_MSGS, MAX_MSG_LEN, MSG_Q_PRIORITY))  
        == NULL) 
        printf("Message Queue error");

}








void receiveTask(void)
{   
    char msgBuf[MAX_MSG_LEN];  


    /* get message from queue; if necessary wait until msg is available */ 
    if (msgQReceive(myMsgQ, msgBuf, MAX_MSG_LEN, WAIT_FOREVER) == ERROR) 
        printf("Error - msgQreceive"); 
 
    /* display message */ 
    printf ("Message from task 1:\n%s\n", msgBuf); 


}   

void sendTask(void)
{ 
  
    char msgBuf[MAX_MSG_LEN];
  
    if (msgQSend (myMsgQ, MESSAGE, sizeof (MESSAGE), WAIT_FOREVER, 
                  MSG_PRI_NORMAL) == ERROR) 
    printf("msgQSend error"); 
  
}   



   
