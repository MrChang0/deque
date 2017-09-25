#include "deque.h"

#include <stdlib.h>
#include <stdio.h>

struct deque_node {
	void * data;
};

struct deque {
	int head;
	int tail;
	int size;
	
	struct deque_node * q;
};

struct deque *
deque_create(int size){
	struct deque * d = malloc(sizeof(struct deque));
	if(d == NULL) return NULL;
	size++;
	d->q = malloc(sizeof(struct deque_node)*size);
	if(d->q == NULL) return NULL;

	d->head = 0;
	d->tail = size - 1;
	d->size = size;
	return d;
}

void
deque_destory(struct deque * d){
	free(d->q);
	free(d);
}

static inline int
isempty(struct deque * d){
	return (d->tail + 1) % d->size == d->head;
}

void *
deque_pop(struct deque * d,int after){
	int pos = 0;
	void * ret;
	if(isempty(d)){
		return NULL;
	}

	if(after){
		d->tail = (d->tail+1) % d->size;
		pos = d->tail; 
	}else{
		d->head = (d->head-1)<0?(d->size -1): (d->head - 1);
		pos = d->head; 
	}
	ret = d->q[pos].data;
	d->q[pos].data = NULL;
	return ret;
}

static void
resize_q(struct deque *d,int resize){
	struct deque_node * n_q = malloc(sizeof(struct deque_node)*resize);
	void * ud = NULL;
	int pos = 0;

	while((ud = deque_pop(d,1)) != NULL){
		n_q[pos].data = ud;
		pos++;
	}
	free(d->q);

	d->q = n_q;
	d->head = pos;
	d->size = resize;
	d->tail = d->size -1;
}

static inline int
isfull(struct deque * d){
	return d->head == d->tail;
}

void
deque_push(struct deque * d,void * data,int after){
	int pos = 0;

	if(isfull(d)){
		resize_q(d,(d->size-1)*2+1);
	}
	if(after){
		pos = d->tail;
		d->tail = (d->tail-1) < 0 ? d->size-1: d->tail-1;
	}else{
		pos = d->head;
		d->head = (d->head+1) % d->size; 
	}

	d->q[pos].data = data;
}

static inline int count_q(struct deque * d){
	return d->head+d->size-d->tail-1;
}

void * deque_at(struct deque * d,int at){
	if(isempty(d) || count_q(d) < at){
		return NULL;
	}
	int pos = (d->tail + at) % d->size;
	return d->q[pos].data;
}

void
deque_dump(struct deque * d,uprint print){
	if(isempty(d)){
		return;
	}
	int i = (d->tail + 1) % d->size;
	for(;i!=d->head;){
		printf("[%d]:",i);
		print(d->q[i].data);
		printf("\n");
		i = (i+1) % d->size;
	}
}