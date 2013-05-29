#ifndef __TREE_H
#define __TREE_H
 
#include "PetriNet.h" 
#include <list> 
 
 struct node{         //each node is a tree in itself
	 
   node *parent;
   
   list<node*> children;
   
   marking label;
  
  // bool visited;
  
  
  node(){
	  //visited = false;
	  }
  
   
};
 
 
 



 
 
 
class kmTree{
 
   node *root;
   PetriNet* P;

public:
       
    kmTree(){
		root = new node;
	}
	
		
	kmTree(PetriNet* Pn){
		root = new node;
		root->parent = NULL ;
		root->label = Pn->getInitialMarking();
		P = Pn;
	}
	
	
	node* expand();  //returns the root of the tree

	
	
       
 };
	
	
	
 
 
 
 
 
 
 
 
 
 
 
#endif 

