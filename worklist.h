#ifndef _WORKLIST_H
#define _WORKLIST_H


#include "tree.h"


struct worklist_manager{
	
	void* (*create)(void);
	void (*put)(void* , void*);
	void* (*get)(void**);
	int (*empty)(void**);
	
} worklist_manager;


static const worklist_manager lifo_manager;

static const worklist_manager fifo_manager;






struct lifo_node{
	lifo_node* next;
	node* x;
}lifo_node;









#endif	/* !_WORKLIST_H */
