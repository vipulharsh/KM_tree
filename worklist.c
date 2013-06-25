#include "worklist.h"



node* lifo_pop(lifo_node **x)
{
	assert((*x)!=NULL);
	lifo_node *t = *x;
	*x = (*x)->next;
	 
	//XXX : might want to free t; 
	node *ret = t->x;
	free(t);
	return ret;
}




int lifo_push(lifo_node **list , node *n)
{
	lifo_node *new = malloc(sizeof(lifo_node));
	
	new->x = n;
	new->next  = *list;
	*list = new;
	return 1;
}


int lifo_empty(lifo_node **list)
{
	return (list==NULL);
}
