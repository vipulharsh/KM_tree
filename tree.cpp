#include "tree.h"

/*
 *Function to compute two things
 * 1)  list of all ancestors which are strictly less than N 
 * 2)  whether N is equal to or less than an ancestor
 */
 
 
 
/* 
struct resultLA{
	bool res;
	bool empty;
	list<int>::const_iterator begin;
	list<int>::const_iterator end;
}; 
*/ 
 


/* 
resultLA* lesserAncestors(node * N){
	
	
	resultLA *res = new resultLA;
	res->res = false;
	
	
	list<int>* placesC; //places which needs to be changed
	
	placesC =  new list<int>;
	
	
	
	
	node *t;
	t = N->parent;
	
	//N->label.display();
	
	while(t != NULL){
		//t->label.display();
		
		//return the places where omega needs to be placed , rather than nodes
		
		if(t->label < N->label) {
			
			for (int i=0; i< N->label.nOfPlaces ; i++){
				if(t->label.tokens[i] < N->label.tokens[i])
					placesC->push_back(i);
			}
		  }	
		
		if(N->label == t->label){ 
			res->res = true;
			break;
		}
		t = t->parent;
	}
	
	
	res->begin  = placesC->begin();
	res->end  = placesC->end();
	res->empty = placesC->empty();
 
 	return res;
}

*/


struct resultLA{
	bool empty;
	list<int>::const_iterator begin;
	list<int>::const_iterator end;
}; 













resultLA* lesserAncestors1(node * N){
	
	
	resultLA *res = new resultLA;
	
	list<int>* placesC; //places which needs to be changed
	
	placesC =  new list<int>;
	
	node *t;
	t = N->parent;
	
	//N->label.display();
	
	while(t != NULL){
		//t->label.display();
		
		//return the places where omega needs to be placed , rather than nodes
		
		if(t->label < N->label) {
			
			for (int i=0; i< N->label.nOfPlaces ; i++){
				if(t->label.tokens[i] < N->label.tokens[i])
					placesC->push_back(i);
			}
		  }	
		
		t = t->parent;
	}
	
	
	res->begin  = placesC->begin();
	res->end  = placesC->end();
	res->empty = placesC->empty();
 
 	return res;
}





bool equalAncestors(node * N){
	
	bool res = false;
	node *t;
	t = N->parent;
	//N->label.display();
	while(t != NULL){
		//t->label.display();
		if(N->label == t->label){ 
			res = true;
			break;
		}
		t = t->parent;
	}
	return res;
}










/*
node* kmTree :: expand(){
	
	cout<<"flag 1"<<endl;
	
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
	  
	  
	  cout<<"flag 2"<<endl;
	  
	  
	  resultLA* result  = lesserAncestors(temp);
	  
	  
	  
	  cout<<"flag 3"<<endl;
	  
	  if(result->res) continue;
	  
	
	
	  //Acceleration
	  if(!result->empty){
		  
		  
	  cout<<"flag 4"<<endl;	  
		  
	  list<int>::const_iterator iterator;
	
	   for (iterator = result->begin; iterator != result->end; ++iterator) {    
			temp->label.tokens[*iterator] = numeric_limits<double>::infinity();
			
		//	
		//	marking ancestor1 = *iterator;
		//	for (int i=0; i< P.getNofPlaces() ; i++){
		//		if(ancestor1.tokens[i] < temp->label.tokens[i])
		//			temp->label.tokens[i] = numeric_limits<double>::infinity();
		//	}
		 
			
	  }
	  
	  
	// unprocessedNodes.push_back(temp);
	// continue; 
	 }       
	  
	  //Add all children of the nodes
	  list<marking> childrenNodes =  P->reachableMarkings(temp->label);
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
*/






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
	  
	  if(!equalAncestors(temp)){
	    //Add all children of the nodes
	  pair< list<marking>::const_iterator, list<marking>::const_iterator> childrenNodes =  P->reachableMarkings(temp->label);
	  list<marking>::const_iterator iterator;
	  
      //  temp->label.display();
	  for (iterator = childrenNodes.first; iterator != childrenNodes.second; ++iterator) {
		  node *N1 = new node;
		  N1->parent  = temp;
		  N1->label = *iterator;
		  
		  resultLA* S  = lesserAncestors1(N1);
		  
		  
		  
		  //Perform Acceleration
		  if(!S->empty){
			 list<int>::const_iterator iterator;
			 for (iterator = S->begin; iterator != S->end; ++iterator)     
			    N1->label.tokens[*iterator] = numeric_limits<double>::infinity();
          }
          
          
          
             temp->children.push_back(N1);
		     unprocessedNodes.push_back(N1);
		    //  N1->label.display();
	   }
	 
      }
  }
  
  return root;
}
	  
	  
	  
	  
	  
	  
	  
	  
	  














