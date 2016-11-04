
#include "vxWorks.h"
#include "stdio.h"
#include "stdlib.h"
#include "Circularbuffer.h"
STATUS start(void)
{  
	Circularbuffer test=new Circularbuffer();
	int *test= int new[5];
	test.Write(*test,5);
	return (OK);
}
void stop(void) {

	return;
}
