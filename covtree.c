#include "covtree.h"


static void
marking_display(const wnat *m)
{
	(void)marking_write(stdout, m);
}




int		 covtree_covers(wnat* m, const node *x){
	list_nodes *unProcessedNodes = NULL;
	node *currNode;
	push_front(&unProcessedNodes , x);
	
	while(unProcessedNodes != NULL){
		 currNode = pop_front(&unProcessedNodes);
		
		if(marking_leq(m , currNode->marking)) return 1;  //m covered by this node , return 1
		
		
		node *temp = currNode->child;
		while(temp!=NULL){
			push_front(&unProcessedNodes , temp);
			temp = temp->next;
		}
		
		
	}
	
	return 0;  //not covered
}
















int		 covtree_complete(const net *PN, const node *x){
	
	wnat *rootMarking = node_root(PN)->marking; //label of the root
	node *tree = x;  // XXX 
	
	list_nodes *unProcessedNodes = NULL;
	
	list_markings *unCheckedMarkings = NULL;
    
    push_frontM(&unCheckedMarkings , rootMarking);
    push_front(&unProcessedNodes , tree);
    


	while(unProcessedNodes != NULL){
		
		node *currNode  = pop_front(&unProcessedNodes);
		
	//	marking_display(currNode->marking);
	//	printf(" 1\n");
			
		int k;
		for(k=0;k<PN->trans_count;k++){
			
			if(!marking_leq(PN->trans[k].input , currNode->marking))  //if this transition is not firable
				continue;
				
			wnat *cMarking = marking_create();  // XXX
			marking_add(cMarking , currNode->marking , PN->trans[k].output);
			marking_sub(cMarking , cMarking , PN->trans[k].input);
		//	marking_display(cMarking);
		//	printf(" 2\n");
			push_frontM(&unCheckedMarkings , cMarking);	
		}
		
		while(unCheckedMarkings != NULL){
			wnat *currMarking = pop_frontM(&unCheckedMarkings);
		//	marking_display(currMarking);
		//	printf(" 3\n");
			int res = covtree_covers(currMarking , x);
			if(res == 0) return 0;    // XXX
		}
		
		node *temp = currNode->child;
		while(temp!=NULL){
			push_front(&unProcessedNodes , temp);
			temp = temp->next;
		}
		
	}
	
	
	return 1;
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











