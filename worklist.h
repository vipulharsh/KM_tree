#ifndef _WORKLIST_H
#define _WORKLIST_H


#include "tree.h"




typedef struct worklist_manager{
	
	void* (*create)(void);
	void (*put)(void* , void*);
	void* (*get)(void**);
	int (*empty)(void**);
	
} worklist_manager;








// LIFO IMPELEMENTATION
//********************************************************************************//
static const worklist_manager lifo_manager;
//XXX	gives an error//lifo_manager.put = lifo_push;
//XXX	gives an error//lifo_manager.get = &lifo_pop; 
//XXX	gives an error//lifo_manager.empty = &lifo_empty;


typedef struct lifo_node{
	struct lifo_node* next;
	node* x;
} lifo_node;

node* lifo_pop(lifo_node **x);
int lifo_push(lifo_node **list , node *n);
int lifo_empty(lifo_node **list);
//*******************************************************************************//
















//FIFO IMPELEMENTATION
//*******************************************************************************//
typedef struct fifo_node{
	struct fifo_node* next;
	node *x;
} fifo_node;

typedef struct fifo_list{
	struct fifo_node* head;
	struct fifo_node* tail;
} fifo_list;


static const worklist_manager fifo_manager;

node* fifo_pop(fifo_list **x);
int fifo_push(fifo_list **list , node *n);
int fifo_empty(fifo_list **list);
//*******************************************************************************//










#endif	/* !_WORKLIST_H */
