#include "vxWorks.h"
#include "stdio.h"
#include "stdlib.h"
#include "Circularbuffer.h"

Circularbuffer::Circularbuffer(){
	buf= int new [N]; 
	count=0;
}
void Circularbuffer::Write(int *p, int n){
	if(count+n<N){
	for(int i=0;i<n;i++){
		buf[count]=p[i];	
		count++;
	}
	}
	
}
void Circularbuffer::Read(int *q, int m){
	if(count-m>N){
		for(int i=0;i<m;i++){
			q[i]=buf[count];
			count--;
	}	
	}
}
