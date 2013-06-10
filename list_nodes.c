#include "list_nodes.h"



node* pop_front(list_nodes **x)
{
	assert((*x)!=NULL);
	list_nodes *t = *x;
	*x = (*x)->next;
	 
	//XXX : might want to free t; 
	node *ret = t->x;
	free(t);
	return ret;
}


int push_front(list_nodes **list , node *n)
{
	list_nodes *new = malloc(sizeof(list_nodes));
	
	new->x = n;
	new->next  = *list;
	*list = new;
	return 1;
}



int empty(list_nodes *x){
return (x==NULL);	
}

