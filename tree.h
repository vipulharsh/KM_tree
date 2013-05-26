#ifndef __TREE_H
#define __TREE_H
 
#include "marking.h" 
 
 
 struct node{         //each node is a tree in itself
	 
   node *parent;
   
   list<node*> children;
   
   marking label;
   
};
 
 
 
 
 
 
class kmTree{
 
   node *root;

public:
       
    kmTree(){
		root = new node;
	}
       
 };
	
	
	
 
 
 
 
 
 
 
 
 
 
 
#endif 

