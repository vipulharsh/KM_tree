#include "tree.h"




/*
 *Function to compute two things
 * 1)  list of all ancestors which are strictly less than N 
 * 2)  whether N is equal to or less than an ancestor
 */
 
 
 
pair<list<marking>,bool> lesserAncestors(node * N){
	
	pair<list<marking> , bool> p;
	p.second =false;
	node *t;
	t = N->parent;
	
	//N->label.display();
	
	while(t != NULL){
		//t->label.display();
		
		//return the places where omega needs to be placed , rather than nodes
		
		if(t->label < N->label) p.first.push_back(t->label);
		if(N->label == t->label){ 
			p.second = true;
			break;
		}
		t = t->parent;
	}
	
	return p;
}







node* kmTree :: expand(){
	
	
	
	if(root == NULL) {
		cout <<"Incorrect call to expand , instantiate the problem first" <<endl;
		return NULL;
	}
	
	list<node*> unprocessedNodes;
	unprocessedNodes.push_back(root);
	
	
	while(!unprocessedNodes.empty())
	{
	  
	  node* temp = unprocessedNodes.front();
	  unprocessedNodes.pop_front();
	  
	  pair <list<marking>,bool> result  = lesserAncestors(temp);
	  
	  if(result.second) continue;
	  
	
	
	  //Acceleration
	  if(!result.first.empty()){
	  list<marking>::const_iterator iterator;
	
	   for (iterator = result.first.begin(); iterator != result.first.end(); ++iterator) {    
			marking ancestor1 = *iterator;
			for (int i=0; i< P.getNofPlaces() ; i++){
				if(ancestor1.tokens[i] < temp->label.tokens[i])
					temp->label.tokens[i] = numeric_limits<double>::infinity();
			}
			
	  }
	  
	  
	// unprocessedNodes.push_back(temp);
	// continue; 
	 }       
	  
	  //Add all children of the nodes
	  list<marking> childrenNodes =  P.reachableMarkings(temp->label);
	  list<marking>::const_iterator iterator;
	  
      //  temp->label.display();
	  for (iterator = childrenNodes.begin(); iterator != childrenNodes.end(); ++iterator) {
		  node *N1 = new node;
		  N1->parent  = temp;
		  temp->children.push_back(N1);
		  N1->label = *iterator;
		  unprocessedNodes.push_back(N1);
		//  N1->label.display();
	}
	  
	  
    }
	return root;
}

