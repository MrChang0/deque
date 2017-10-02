#ifndef _DEQUE_H
#define _DEQUE_H
struct deque;

struct deque * deque_create(int size);
void deque_destory(struct deque * d);
void deque_push(struct deque * d,void * data,int after);
void * deque_pop(struct deque * d,int after);

void * deque_at(struct deque * d,int);

#ifdef DEBUG
typedef void (*uprint)(void * data);
void deque_dump(struct deque * d,uprint print);
#endif

#endif