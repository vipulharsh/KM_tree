#ifndef __TREE_H
#define __TREE_H
 
#include "PetriNet.h" 
#include <list> 
 
 struct node{         //each node is a tree in itself
	 
   node *parent;
   
   list<node*> children;
   
   marking label;
   
};
 
 
 
 
 
 
class kmTree{
 
   node *root;
   PetriNet P;

public:
       
    kmTree(){
		root = new node;
	}
	
		
	kmTree(marking initialMarking , PetriNet Pn){
		root = new node;
		root->parent = NULL ;
		root->label = initialMarking;
		P = Pn;
	}
	
	
	void expand();

	
	
       
 };
	
	
	
 
 
 
 
 
 
 
 
 
 
 
#endif 

