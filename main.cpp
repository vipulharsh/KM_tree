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
    
    
    
    t.expand();
    
	
	return 0;
}

