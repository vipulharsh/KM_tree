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
			
		unsigned int k;
		for(k=0;k<PN->trans_count;k++){
			
			if(!marking_leq(PN->trans[k].input , currNode->marking))  //! this transition is not firable
				continue;
				
			
			//!else
			wnat *cMarking = marking_create();  //!XXX
			marking_add(cMarking , currNode->marking , PN->trans[k].output);
			marking_sub(cMarking , cMarking , PN->trans[k].input);
			list_manager.put(unCheckedMarkings , cMarking);	
		}
		
		while(!list_manager.empty(unCheckedMarkings)){
			wnat *currMarking = list_manager.get(unCheckedMarkings);
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
		
	wlmgr->destroy(unprocessedNodes);
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
		
	wlmgr->destroy(unprocessedNodes);
	return root;
}





/*
 * removes the node x and the arc from x to its ancestor
 * Assumption : x can't be the root
 */ 
static
int remove_node(node *x){
	node *parent = x->parent;
	assert(parent!=NULL);
	
	node *child = parent->child;
	
	if(child == x) {
	  parent->child = x->next;
	  node_destroy(x);
	  return 1;
    }
	
	while(child->next != x){
		child = child->next;
		assert(child!=NULL);
	}
	child->next = x->next;
	node_destroy(x);
	return 1;	
	
}






/*
 * removes the node x and it's entire subtree
 */ 
static
int remove_tree(node *x){
	
	void *unProcessedNodes = list_manager.create();
	node *currNode;
	node *temp = x->child;              //add children of x to unprocessed nodes
	while(temp!=NULL){
		list_manager.put(unProcessedNodes , temp);
		temp = temp->next;
	}
	while(!list_manager.empty(unProcessedNodes)){
		currNode = list_manager.get(unProcessedNodes);
#ifdef DEBUG
		marking_display(currNode->marking);
#endif		
		temp = currNode->child;        //add children of this node to unprocessed nodes
		while(temp!=NULL){
			list_manager.put(unProcessedNodes , temp);
			temp = temp->next;
		}
	   node_destroy(currNode);	
	}
	
	list_manager.destroy(unProcessedNodes);
	x->child = NULL;
	return 1;	
	
}




static 
int comparison_processed(const node *x , const node *root){
	
	
	void *unProcessedNodes = list_manager.create();
	node *currNode;
	list_manager.put(unProcessedNodes , root);
	
	while(!list_manager.empty(unProcessedNodes)){
		currNode = list_manager.get(unProcessedNodes);
		
		if(currNode->processed == 0) continue;
		
		if(marking_eq(x->marking , currNode->marking)){
			list_manager.destroy(unProcessedNodes);
			return 1;   //x covered by currNode , return 1
		}
		  
		if(marking_le(x->marking , currNode->marking)){
			list_manager.destroy(unProcessedNodes);
			return 2;  //x covered by currNode , return 2
		}
				 
		  
		if(marking_le(currNode->marking , x->marking)){
			list_manager.destroy(unProcessedNodes);
			return 3;  //x covers curr_node , return 3
		}
				
		node *temp = currNode->child;        //add children of this node to unprocessed nodes
		while(temp!=NULL){
			list_manager.put(unProcessedNodes , temp);
			temp = temp->next;
		}

 
	}
	
	list_manager.destroy(unProcessedNodes);	  
	return 0;	
}




node		*covtree_finkel_mct(const net *PN, const colmgr *wlmgr){
	
	node *root = node_root(PN);
	void *unprocessedNodes = wlmgr->create() ;
	wlmgr->put(unprocessedNodes , root);
	root->processed = 0;
	node *curr_node;
	
	while(!wlmgr->empty(unprocessedNodes)){
		
		curr_node = wlmgr->get(unprocessedNodes);  //!Node to be processed
#ifdef DEBUG
		printf("curr node is ");
		marking_display(curr_node->marking);
		printf("\n");
#endif

//*********************		
		int result = comparison_processed(curr_node , root);
//************************		  
		
		
		
		//!Case 1:
		if(result==1){     //!check for termination condition of the branch
#ifdef DEBUG
 			marking_display(curr_node->marking);
			printf(" Branch ends here \n");
			curr_node->processed = 1;
#endif
			 continue;
		}
		
	
			//!Case 2:
		if(result==2){     //!check for termination condition of the branch
#ifdef DEBUG
 			marking_display(curr_node->marking);
			printf(" Branch ends here \n");
#endif
			remove_node(curr_node);
			 continue;
		}
	
		
		
		//!Case 3:
		if(result==3){
			
			int t = accel(curr_node);
			if(t == 1){
				node *first_ancestor;
				node *p = curr_node;
				while(p!=root){
					if(marking_le(p->marking , curr_node->marking))
					first_ancestor = p;
					p = p->parent;
				}
			    marking_copy(first_ancestor->marking , curr_node->marking);
			    //FILE *fp1= fopen("results/out.txt","a");
			    remove_tree(first_ancestor);
			    curr_node = first_ancestor;		
			  }
			
		//a breadth first search to delete smaller nodes and subtrees.
			void *unExploredNodes = list_manager.create();
			node *x;
			list_manager.put(unExploredNodes , root);
			while(list_manager.empty(unExploredNodes)){
				x = list_manager.get(unExploredNodes);
				if(marking_le(x->marking , 	curr_node->marking)){
					remove_tree(x);
					remove_node(x);
				}
				else{
				node *temp1 = x->child;        //add children of this node to unprocessed nodes
					while(temp1!=NULL){
					list_manager.put(unExploredNodes , temp1);
					temp1 = temp1->next;
				}
			   }	
			}
		}		
			
			
			
		//else
		
		
		
		
		node_expand_all(PN , curr_node);
		
		
		
		
		
		//pushing children of currNode to unprocessed Nodes . 
		
		//printf("Pushing children ");
		curr_node->processed = 1;
		node *descendant = curr_node->child;
		while(descendant!=NULL){
			wlmgr->put(unprocessedNodes , descendant);
#ifdef DEBUG
			marking_display(descendant->marking);
#endif
			descendant->processed = 0;
			descendant = descendant->next;
		
		}
					
		
			
	}
	
	list_manager.destroy(unprocessedNodes);
	return root;
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
	
	int res=0;
	
	node *ancestor = x->parent;
	while(ancestor != NULL){
	  if(marking_le(ancestor->marking , accel_ret)){
			res=1;
			unsigned int j;
			for(j=0;j<dimension;j++){
				if(wnat_le(ancestor->marking[j], accel_ret[j]))
				   x->marking[j] = omega;
			}
		}
		
	ancestor = ancestor->parent;	
	}
	return res;
}











