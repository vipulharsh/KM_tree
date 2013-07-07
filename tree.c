#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "marking.h"
#include "tree.h"

/*
 * node_write_helper:
 *
 *	Helper function for node_write.  Takes the number of spaces as the
 *	argument.
 *
 *	Can be changed later.
 */
static void	 node_write_helper(FILE *stream, const node *, int);


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
	ret->cover=NULL;
	(void)memset(ret, 0, sizeof(node));
	marking_copy(ret->marking, pn->init);
	return ret;
}



void
node_expand_all(const net *pn, node *x)
{
	int count = 0;
	
	unsigned int k;
	
	struct node *curr;
	
	for(k=0;k<pn->trans_count;k++){
		
		//printf(" fl 3 \n");
		
		if(!marking_leq(pn->trans[k].input , x->marking))  //if this transition is not firable
			continue;
		
		
		//else
		
		
		
		node *child = node_create();
		child->action = &(pn->trans[k]);
		child->parent = x;
		child->next = NULL;
		child->cover = NULL;
		child->child = NULL;
		
		
			
		if(count == 0){                   //for the first-child
			x->child =child;
			marking_add(child->marking , x->marking , pn->trans[k].output);
			marking_sub(child->marking , child->marking , pn->trans[k].input);
			curr = child;
			count++;
			continue; 
		}
		
		//else if        			//for the second child and children hence
		 curr->next =child;
		 //child->marking = x->marking + transition.output - transition.input
		 marking_add(child->marking , x->marking , pn->trans[k].output);
		 marking_sub(child->marking , child->marking , pn->trans[k].input);
		 curr = child;
		 assert(child->child == NULL);
		 
		 
		 
		 
		 
	}
	
//end of function
}




int
node_write(FILE *stream, const node *x)
{
	if(x == NULL)
		return 1;

	node_write_helper(stream, x, 0);
//	printf("wain ?\n");
	return 1;
}





void
node_write_helper(FILE *stream, const node *x, int spaces)
{
	int i;
//	printf("hain ? %d \n",spaces);
	
	node *currNode = x->child;

	if(x == NULL)
		return;

	for(i = 0; i < spaces; i++)
		fprintf(stream, "  ");

	marking_write(stream, x->marking);
	fprintf(stream, "\n");

	while(currNode != NULL) {
		node_write_helper(stream, currNode, spaces+1);
		currNode = currNode->next;
	}
}












	
	
	
	
	
