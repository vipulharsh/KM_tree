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
typedef struct lifo_node{
	struct lifo_node* next;
	node* x;
} lifo_node;

lifo_node* lifo_create();
node* lifo_pop(lifo_node **x);
int lifo_push(lifo_node **list , node *n);
int lifo_empty(lifo_node **list);

//XXX : declaration not working
// static const worklist_manager lifo_manager={&lifo_create , &lifo_pop , &lifo_push , &lifo_empty};
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

fifo_node* fifo_create();
node* fifo_pop(fifo_list **x);
int fifo_push(fifo_list **list , node *n);
int fifo_empty(fifo_list **list);

//XXX : declaration not working
//static const worklist_manager fifo_manager={&fifo_create , &fifo_pop , &fifo_push , &fifo_empty};
//*******************************************************************************//












//DICTIONARY IMPLEMENTATION 
//**************************************************************************//
typedef struct pair{
	char key[80];
	int val;
	struct pair* next;
}pair;

pair* pair_create();
pair* pair_pop(pair **x);
int pair_push(pair **list , pair *n);
int pair_empty(pair **list);


//XXX: declaration not working
//static const worklist_manager dictionary_manager={&pair_create , &pair_pop , &pair_push , &pair_empty};
//***************************************************************************










#endif	/* !_WORKLIST_H */
