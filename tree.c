#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "marking.h"
#include "tree.h"

node *
node_create(void)
{
	assert(dimension > 0);
	return malloc(sizeof(node) + dimension * sizeof(wnat));  
}

void
node_destroy(node *x)
{
	free(x);
}

node *
node_root(const net *pn)
{
	node *ret;

	ret = node_create();
	(void)memset(ret, 0, sizeof(node));
	marking_copy(ret->marking, pn->init);
	return ret;
}



void
node_expand_all(const net *pn, node *x)
{
	int count = 0;
	
	int k;
	
	struct node *curr;
	
	for(k=0;k<pn->trans_count;k++){
		
		if(le(x->marking , pn->trans[k].input))  //if this transition is not firable
			continue;
		
		//else
		if(count = 0){
			node *child = node_create();
			x->child =child;
			child->action = &(pn->trans[k]);
			child->parent = x;
			child->next = NULL;
			marking_add(child->marking , x->marking , pn->trans[k].output);
			curr = child;
			count++;
			continue; 
		}
		
		//else if
		 node *child = node_create();
		 curr->next =child;
		 child->action = &(pn->trans[k]);
		 child->parent = x;
		 child->next = NULL;
		 marking_add(child->marking , x->marking , pn->trans[k].output);
		 curr = child;
	}
//end of function
}
	
	
	
	
	
