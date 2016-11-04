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

#define TIMESLICE sysClkRateGet()

void taskOne(void);
void taskTwo(void);

SEM_ID semBinary;
int global = 0;

STATUS start(void) {

	pthread_t tid1, tid2;
	pthread_attr_t attr;
	struct sched_param AppSchedPrio;
	pthreadLibInit();
	if (kernelTimeSlice(10) != OK)
		printf("Time slice error");

	semBinary = semBCreate(SEM_Q_FIFO, SEM_FULL);

	if (pthread_attr_init(&attr) != 0)
		printf("\n thread attribute object init error");

	/* create the pthreads */
	if (pthread_create(&tid1, &attr, taskOne, 0) != 0)
		printf("\n thread 1 create error");
	if (pthread_create(&tid2, &attr, taskTwo, 0) != 0)
		printf("\n thread 2 create error");
	AppSchedPrio.sched_priority = 90;
	pthread_setschedparam(tid1, SCHED_RR, &AppSchedPrio);
	pthread_setschedparam(tid2, SCHED_RR, &AppSchedPrio);

	return (OK);

}

void taskOne(void) {
	int j;
	while (1) {
		semTake(semBinary, WAIT_FOREVER);
		for (j = 0; j < 20; j++) {
			printf("I am task one and global = %d....\n", ++global);
			taskDelay(TIMESLICE);
		}
		semGive(semBinary);
	}

}

void taskTwo(void) {
	int i;

	while (1) {
		semTake(semBinary, WAIT_FOREVER);
		for (i = 0; i < 20; i++) {
			printf("I am task two and global = %d....\n", --global);
			taskDelay(TIMESLICE);
		}
		semGive(semBinary);

	}
}

void stop(void) {
	//taskDelete (taskIdOne);
	// taskDelete (taskIdTwo);
	// taskDelete (taskIdThree);
	// taskDelete (taskIdFour);

	semDelete(semBinary);

	return;
}

