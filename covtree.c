#include "covtree.h"


node* pop_front(list_nodes **x)
{
	
	
	assert((*x)!=NULL);
	
	list_nodes *t = *x;
	*x = (*x)->next;
	 
	//XXX : might want to free t; 
	
	return t->x;
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












node* covtree_original_km(const net *PN){
	node *root = node_root(PN);
	list_nodes *unprocessedNodes = NULL ;
	push_front(&unprocessedNodes , root);
	
	node *curr_node;
	
	
	while(!empty(unprocessedNodes)){
		

			
		
		printf("inside loop\n");
		
		
		
		curr_node = pop_front(&unprocessedNodes);
		
	
		FILE *file;
		file = fopen("side.txt","w");
		
	//	printf("flag 9 \n");
		
	//	node_write(curr_node , file);
		
	//	printf("flag 10 \n");
		fprintf(file, "done\n");
		fclose(file);

	
	
		marking_display(curr_node->marking);
		
	/*	
		printf("parent is :  ");
		if(curr_node->parent != NULL){
			marking_display(curr_node->parent->marking);
		//	printf("equal ancestors result %d \n" , equal_ancestor(curr_node));
		}		
		else
		  printf(" NULL ");
		  
		 printf("\n"); 
	*/	
		//printf("flag 1");
		
		
		
		if(equal_ancestor(curr_node)){
			marking_display(curr_node->marking);
			printf("ends here");
			 continue;
		}
		
		//printf("flag 2");
		
		//else
		node_expand_all(PN , curr_node);
		
		//pushing children of currNode to unprocessed Nodes . 
		//Acceleration is also done here
		printf("Pushing children \n");
		node *temp = curr_node->child;
		while(temp!=NULL){
			accel(temp);
			push_front(&unprocessedNodes , temp);
			marking_display(temp->marking);
			temp = temp->next;
		}
		//printf("flag 3");
		
	}//end of while loop
		
	
	return root;
}











int equal_ancestor(node* x)
{
	node *ancestor = x->parent;
	
/*
	printf("\n\n\n\n\n\n\n\n");
    printf("inside equal_ancestor\n");
	printf("node is :");
	marking_display(x->marking);
	printf("\n");
*/	
 // printf("Beginning of equal ancestor\n\n");

	while(ancestor != NULL){
		//marking_display(ancestor->marking);
		//printf("  ");
		//marking_display(x->marking);
		//printf("\n");
		if(marking_eq(x->marking , ancestor->marking)) return 1;
		//printf("\n");
		ancestor = ancestor->parent;
	}
	
	//printf("end of equal_ancestor\n\n");
	
	return 0;	 
}











int accel(node *x)
{
	
	wnat *ret = marking_create(); //XXX : avoid malloc if possible
	
	marking_copy(ret, x->marking); 
	
	node *ancestor = x->parent;
	
	
	while(ancestor != NULL){
	  	 
	  if(marking_le(ancestor->marking , ret)){
			int j;
			for(j=0;j<dimension;j++){
				if(wnat_le(ancestor->marking[j], ret[j]))
				   x->marking[j] = omega;
			}
		}
		
	ancestor = ancestor->parent;	
		
	}
	
	marking_destroy(ret);
	
	return 1;
}











