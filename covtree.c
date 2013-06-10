#include "covtree.h"





node* covtree_original_km(const net *PN){
	node *root = node_root(PN);
	list_nodes *unprocessedNodes = NULL ;
	push_front(&unprocessedNodes , root);
	
	node *curr_node;
	
	
	while(!empty(unprocessedNodes)){
		
	//	printf("inside loop\n");
		
		curr_node = pop_front(&unprocessedNodes);  //!Node to be processed
	
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
		
		
		
		if(equal_ancestor(curr_node)){     //!check for termination condition of the branch
 			marking_display(curr_node->marking);
			printf(" Branch ends here \n");
			 continue;
		}
		
		
		//else
		node_expand_all(PN , curr_node);
		
		//pushing children of currNode to unprocessed Nodes . 
		//Acceleration is also done here
		
		//printf("Pushing children \n");
		
		node *temp = curr_node->child;
		while(temp!=NULL){
			accel(temp);
			push_front(&unprocessedNodes , temp);
			marking_display(temp->marking);
			temp = temp->next;
		}
		
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











