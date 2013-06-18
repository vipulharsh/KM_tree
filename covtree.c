#include "covtree.h"


static void
marking_display(const wnat *m)
{
	(void)marking_write(stdout, m);
}






node* covtree_original_km(const net *PN){
	node *root = node_root(PN);
	list_nodes *unprocessedNodes = NULL ;
	push_front(&unprocessedNodes , root);
	
	node *curr_node;
	
	
	while(!empty(unprocessedNodes)){
		
		
		curr_node = pop_front(&unprocessedNodes);  //!Node to be processed
#ifdef DEBUG
		marking_display(curr_node->marking);
#endif

	/*	
		printf("parent is :  ");
		if(curr_node->parent != NULL){
			marking_display(curr_node->parent->marking);
		//	printf("equal ancestors result %d \n" , equal_ancestor(curr_node));
		}		
		else
		  printf(" NULL ");
		*/
		
		
		
		if(equal_ancestor(curr_node)){     //!check for termination condition of the branch
#ifdef DEBUG
 			marking_display(curr_node->marking);
			printf(" Branch ends here \n");
#endif
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
#ifdef DEBUG
			marking_display(temp->marking);
#endif
			temp = temp->next;
		}
		
	}//end of while loop
		
	
	return root;
}











int equal_ancestor(node* x)
{
	node *ancestor = x->parent;
	
	

	while(ancestor != NULL){
		//marking_display(ancestor->marking);
		//marking_display(x->marking);
		if(marking_eq(x->marking , ancestor->marking)) return 1;
		ancestor = ancestor->parent;
	}
	
	return 0;	 
}







static wnat *ret = NULL;



int accel(node *x)
{
	if(ret == NULL)
	ret = marking_create(); //XXX : avoid malloc if possible
	
	
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
	
	//marking_destroy(ret);
	
	return 1;
}











