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
	
	//printf("ok till here %d \n ", pn->trans_count);
	
	for(k=0;k<pn->trans_count;k++){
		
		//printf(" fl 3 \n");
		
		if(!marking_leq(pn->trans[k].input , x->marking))  //if this transition is not firable
			continue;
		
		//else
		if(count == 0){
			node *child = node_create();
			x->child =child;
			child->action = &(pn->trans[k]);
			child->parent = x;
			child->next = NULL;
			marking_add(child->marking , x->marking , pn->trans[k].output);
			marking_sub(child->marking , child->marking , pn->trans[k].input);
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
		 
		 //child->marking = x->marking + transition.output - transition.input
		 
		 marking_add(child->marking , x->marking , pn->trans[k].output);
		 marking_sub(child->marking , child->marking , pn->trans[k].input);
		 curr = child;
	}
//end of function
}




int
node_write(const node *x, FILE *stream)
{
	if(x == NULL) return 1;
	
	node_write_helper(x , stream ,0);
	
	return 1;
	
}





void
node_write_helper(const node *x, FILE *stream, int spaces)
{
	if(x == NULL) return;
	
	int i;
	
	printf("once %d\n ", x==NULL);
	
	node *currNode = x->child;
	
	printf("twice \n");
	for(i=0;i<spaces;i++)
		fprintf(stream , "  ");	
	marking_write(x->marking , stream);
	fprintf(stream , "\n");
	
	while(currNode!=NULL){
		node_write_helper(currNode, stream , spaces+1);
		currNode = currNode->next;
	}
		
	
}












	
	
	
	
	
