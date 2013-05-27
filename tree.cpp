#include "tree.h"





pair<list<marking>,bool> lesserAncestors(node * N){
	
	pair<list<marking> , bool> p;
	p.second =false;
	node *t;
	t = N->parent;
	
	cout<<"in here lesser Ancestors"<<endl;
	N->label.display();
	
	
	
	while(t != NULL){
		t->label.display();
		if(t->label < N->label) p.first.push_back(t->label);
		if(N->label == t->label) p.second = true;
		t = t->parent;
	}
	
	cout<<"end of lesser Ancestors"<<endl;
	return p;
}







void kmTree :: expand(){
	
	cout<<endl<<"1"<<endl;
	
	
	if(root == NULL) {
		cout <<"Incorrect call to expand , instantiate the problem first" <<endl;
		return;
	}
	
	list<node*> unprocessedNodes;
	unprocessedNodes.push_back(root);
	
	
	while(!unprocessedNodes.empty())
	{
	  
	  
	  cout<<endl<<"2"<<endl;
	
	  node* temp = unprocessedNodes.front();
	  unprocessedNodes.pop_front();
	  
	  pair <list<marking>,bool> result  = lesserAncestors(temp);
	  
	  if(result.second) continue;
	  
	  
	  
	  
	  //Acceleration
	  if(!result.first.empty()){
	  list<marking>::const_iterator iterator;
	
	  cout<<endl<<"part2"<<endl;
	   for (iterator = result.first.begin(); iterator != result.first.end(); ++iterator) {    
			marking ancestor1 = *iterator;
			for (int i=0; i< P.getNofPlaces() ; i++){
				if(ancestor1.tokens[i] < temp->label.tokens[i])
					temp->label.tokens[i] = numeric_limits<double>::infinity();
			}
			
	  }
	 }       
	  
	  //Add all children of the nodes
	  list<marking> childrenNodes =  P.reachableMarkings(temp->label);
	  list<marking>::const_iterator iterator;
	  
	  cout<<"part3"<<endl;
	  temp->label.display();
	  for (iterator = childrenNodes.begin(); iterator != childrenNodes.end(); ++iterator) {
		  node *N1 = new node;
		  N1->parent  = temp;
		  temp->children.push_back(N1);
		  N1->label = *iterator;
		  unprocessedNodes.push_back(N1);
		  N1->label.display();
	}
	  
	  
    }
	
}

