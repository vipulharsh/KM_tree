#include "tree.h"





pair<list<node*>,bool> lesserAncestors(node * N){
	
	pair<list<node*> , bool> p;
	p.second =false;
	node *t;
	t = N->parent;
	while(t != NULL){
		if(N->label < t->label) p.first.push_back(t);
		if(N->label == t->label) p.second = true;
		t = t->parent;
	}
	return p;
}







void kmTree :: expand(){
	if(root == NULL) {
		cout <<"Incorrect call to expand , instantiate the problem first" <<endl;
		return;
	}
	
	list<node*> unprocessedNodes;
	unprocessedNodes.push_back(root);
	{
	  node* temp = unprocessedNodes.front();
	  unprocessedNodes.pop_front();
	  
	  //list<node*> lesserAncestors1 = lesserAncestors(temp);
	  
	  
    }
	
}
