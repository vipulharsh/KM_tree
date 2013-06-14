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







node* pop_back(list_nodes **x){
	
	
	
	
	node *ret;
	return ret;
}
node* pop(list_nodes **x){
	
	return ((*popF)(x));
	
}



node* push(list_nodes **x){
	
	return ((*push)(x));
	
}






int push_back(list_nodes **list ,  node *n){
	
	
	
	return 1;
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

