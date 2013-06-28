#include "covtree.h"


static void
marking_display(const wnat *m)
{
	(void)marking_write(stdout, m);
}




int		 covtree_covers(wnat* m, const node *x){
	void *unProcessedNodes = list_manager.create();
	node *currNode;
	list_manager.put(unProcessedNodes , x);
	
	while(!list_manager.empty(unProcessedNodes)){
		currNode = list_manager.get(unProcessedNodes);
		if(marking_leq(m , currNode->marking)){
			 list_manager.destroy(unProcessedNodes);
			 return 1;  //m covered by this node , return 1
		  }
		node *temp = currNode->child;        //add children of this node to unprocessed nodes
		while(temp!=NULL){
			list_manager.put(unProcessedNodes , temp);
			temp = temp->next;
		}	
	}
	list_manager.destroy(unProcessedNodes);
	return 0;  //not covered
}








int		 covtree_complete(const net *PN, const node *x){
	
	wnat *rootMarking = node_root(PN)->marking; //label of the root
	const node *tree = x;  // XXX 
	void *unProcessedNodes = list_manager.create();
	void *unCheckedMarkings = list_manager.create();
    
    list_manager.put(unCheckedMarkings , rootMarking);
    list_manager.put(unProcessedNodes , tree);
    
	while(!list_manager.empty(unProcessedNodes)){
		
		node *currNode  = list_manager.get(unProcessedNodes);
		
	//	marking_display(currNode->marking);
	//	printf(" 1\n");
			
		int k;
		for(k=0;k<PN->trans_count;k++){
			
			if(!marking_leq(PN->trans[k].input , currNode->marking))  //! this transition is not firable
				continue;
				
			
			//!else
			wnat *cMarking = marking_create();  //!XXX
			marking_add(cMarking , currNode->marking , PN->trans[k].output);
			marking_sub(cMarking , cMarking , PN->trans[k].input);
		//	marking_display(cMarking);
		//	printf(" 2\n");
			list_manager.put(unCheckedMarkings , cMarking);	
		}
		
		while(!list_manager.empty(unCheckedMarkings)){
			wnat *currMarking = list_manager.get(unCheckedMarkings);
		//	marking_display(currMarking);
		//	printf(" 3\n");
			int res = covtree_covers(currMarking , x);
			if(res == 0) return 0;    //!XXX
		}
		
		node *temp = currNode->child;          //!add children of this node to unprocessed nodes
		while(temp!=NULL){
			list_manager.put(unProcessedNodes , temp);
			temp = temp->next;
		}
		
	}
	
	list_manager.destroy(unProcessedNodes);
	list_manager.destroy(unCheckedMarkings);
	return 1;
}












node* covtree_reduced_km(const net *PN, const colmgr *wlmgr){
	
	node *root = node_root(PN);
	void *unprocessedNodes = wlmgr->create() ;
	wlmgr->put(unprocessedNodes , root);
	
	node *curr_node;
	
	while(!wlmgr->empty(unprocessedNodes)){
		
		curr_node = wlmgr->get(unprocessedNodes);  //!Node to be processed
#ifdef DEBUG
		marking_display(curr_node->marking);
#endif

	/*	
		printf("parent is :  ");
		if(curr_node->parent != NULL){
			marking_display(curr_node->parent->marking);
		}		
		else
		  printf(" NULL ");
	*/
		
		
		node *res=leq_ancestor(curr_node);
		if(res!=NULL){     //!check for termination condition of the branch
#ifdef DEBUG
 			marking_display(curr_node->marking);
			printf(" Branch ends here \n");
#endif
			 curr_node->cover = res;
			 continue;
		}
		
		
		//else
		curr_node->cover = NULL;
		node_expand_all(PN , curr_node);
		//!pushing children of currNode to unprocessed Nodes . 
		//!Acceleration is also done here
		node *temp = curr_node->child;         
		while(temp!=NULL){
			accel(temp);
			wlmgr->put(unprocessedNodes , temp);
#ifdef DEBUG
			marking_display(temp->marking);
#endif
			temp = temp->next;
		}
		
	}//end of while loop
		
	list_manager.destroy(unprocessedNodes);
	return root;
}








node* covtree_original_km(const net *PN, const colmgr *wlmgr){
	node *root = node_root(PN);
	void *unprocessedNodes = wlmgr->create() ;
	wlmgr->put(unprocessedNodes , root);
	
	node *curr_node;
	
	while(!wlmgr->empty(unprocessedNodes)){
		
		curr_node = wlmgr->get(unprocessedNodes);  //!Node to be processed
#ifdef DEBUG
		marking_display(curr_node->marking);
#endif
	   /*	
		printf("parent is :  ");
		if(curr_node->parent != NULL){
			marking_display(curr_node->parent->marking);
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
			wlmgr->put(unprocessedNodes , temp);
#ifdef DEBUG
			marking_display(temp->marking);
#endif
			temp = temp->next;
		}
		
	}//end of while loop
		
	list_manager.destroy(unprocessedNodes);
	return root;
}




















node		*covtree_finkel_mct(const net *PN, const colmgr *wlmgr){
	return NULL;
}
	





node* leq_ancestor(node* x)
{
	node *ancestor = x->parent;
	while(ancestor != NULL){
		//marking_display(ancestor->marking);
		//marking_display(x->marking);
		if(marking_leq(x->marking , ancestor->marking)) return ancestor;
		ancestor = ancestor->parent;
	}
	return NULL;	 
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







static wnat *accel_ret = NULL;    //Global variable for accel


int accel(node *x)
{
	if(accel_ret == NULL)
	accel_ret = marking_create(); //XXX : avoid malloc if possible
	
	marking_copy(accel_ret, x->marking); 
	
	node *ancestor = x->parent;
	while(ancestor != NULL){
	  if(marking_le(ancestor->marking , accel_ret)){
			int j;
			for(j=0;j<dimension;j++){
				if(wnat_le(ancestor->marking[j], accel_ret[j]))
				   x->marking[j] = omega;
			}
		}
		
	ancestor = ancestor->parent;	
	}
	return 1;
}











