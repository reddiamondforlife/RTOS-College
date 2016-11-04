/* Source code van Voorbeeld 1*/

#include "vxWorks.h"
#include "stdio.h"
#include "stdlib.h"
#include "posixName.h"
#include "pthread.h"
#include "sched.h"
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
int global = 0;
int pos=0;
int *buff;
STATUS start(void) {
	pthread_t tid1, tid2, tid3;
	pthread_attr_t attr;
	struct sched_param AppSchedPrio;
	pthreadLibInit();
	if (kernelTimeSlice(10) != OK)
		printf("Time slice error");

	semBinary = semMCreate(SEM_Q_PRIORITY|SEM_INVERSION_SAFE);

	if (pthread_attr_init(&attr) != 0)
		printf("\n thread attribute object init error");

	/* create the pthreads */
	if (pthread_create(&tid1, &attr, taskOne, 0) != 0)
		printf("\n thread 1 create error");
	if (pthread_create(&tid2, &attr, taskTwo, 0) != 0)
		printf("\n thread 2 create error");
	if (pthread_create(&tid3, &attr, taskThree, 0) != 0)
			printf("\n thread 3 create error");
	AppSchedPrio.sched_priority = 90;
	pthread_setschedparam(tid1, SCHED_RR, &AppSchedPrio);
	pthread_setschedparam(tid2, SCHED_RR, &AppSchedPrio);
	AppSchedPrio.sched_priority = 100;
	pthread_setschedparam(tid3, SCHED_RR, &AppSchedPrio);
	return (OK);

}

void Write(int n){
buff[pos]=n;
		pos++;
}
int Read(int *p){
	*p=*buff;
return 	pos;
}
void taskOne(void) {
	int i;
	while (1) {
		
		semTake(semBinary, WAIT_FOREVER);
		if(pos<10)Write(1);
		taskDelay(TIMESLICE);
		semGive(semBinary);
	}

}

void taskTwo(void) {
	int i;

	while (1) {
		
		semTake(semBinary, WAIT_FOREVER);
		if(pos<10)Write(2);
		taskDelay(TIMESLICE);
		semGive(semBinary);

	}
}
void taskThree(void) {
	

	while (1) {
		
		semTake(semBinary, WAIT_FOREVER);
		int *p=0;
		int t=read(*p);
		int n;
		for(n=0;n<t;n++){
			printf("value on pos %d is %d",t,p[t]);
		}
		semGive(semBinary);
		taskDelay(TIMESLICE*10);
	}
}

void stop(void) {


	semDelete(semBinary);

	return;
}

