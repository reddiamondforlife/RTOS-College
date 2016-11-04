#define N 40

#include "vxWorks.h"
#include "stdio.h"
#include "stdlib.h"
#include "semLib.h"
#include "taskLib.h"
#include "logLib.h"
class Circularbuffer {
private:
	int *buf;
	int count;

public:
	Circularbuffer();
	void Write(int *p, int n);
	void Read(int *q, int m);
};
