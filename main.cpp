#include <iostream>
using namespace std;


#include "PetriNet.h"
#include "tree.h"








int main(){
	
	PetriNet *P; 
	
	P = new PetriNet;
	
	P->instantiate();
	
	
	P->display();
	
	
	list<marking> trying =  P->reachableMarkings(P->getInitialMarking());
	
	list<marking>::const_iterator iterator;
	
	cout<<endl<<"from here"<<endl;
	for (iterator = trying.begin(); iterator != trying.end(); ++iterator) {    
    marking temp = *iterator;
    
    temp.display();
    
    
    }

	
	
	
	
	kmTree t(*P);
    
    
    
    node *km = t.expand();
    

	
	cout<<endl<<endl<<"The tree"<<endl;
	
	
   list<node *> var;
   var.push_back(km);
   
   while(!var.empty()){
	   node *a= var.front();
	   var.pop_front();
	   a->label.display();
	   list<node *>::const_iterator iterator;
	   for (iterator = a->children.begin(); iterator != a->children.end(); ++iterator) {    
          var.push_back(*iterator);
        }
	}
	
	
	
	
	
	
	return 0;
}

