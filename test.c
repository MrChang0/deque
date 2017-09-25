#include <stdio.h>
#include <assert.h>

#include "deque.h"

#define SIZE 64

void mprint(void * d){
	int n = *((int *)d);
	printf("%d",n);
}

int main(){
	struct deque * d = deque_create(SIZE);
	deque_dump(d,mprint);
	int a[SIZE*2];
	int i;
	for(i = 0;i < SIZE; ++i){
		a[i] = i;
		deque_push(d,(void *)&(a[i]),0);
	}
	deque_dump(d,mprint);
	printf("**************************\n");
	for(i = SIZE;i < SIZE*2; ++i){
		a[i] = i*2;
		deque_push(d,(void *)&(a[i]),1);
	}
	deque_dump(d,mprint);
	printf("**************************\n");
	for(i = SIZE*2 - 1;i >= SIZE; --i){
		int * p = deque_pop(d,1);
		int n = *p;
		assert(n == a[i]);
	}
	deque_dump(d,mprint);
	printf("**************************\n");
	for(i = SIZE-1;i >= 0; --i){
		int * p = deque_pop(d,0);
		int n = *p;
		assert(n == a[i]);
	}
	printf("test successful\n");
	deque_destory(d);
}