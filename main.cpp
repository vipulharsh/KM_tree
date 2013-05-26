#include <iostream>
using namespace std;


#include "PetriNet.h"
#include "tree.h"








int main(){
	
	PetriNet *P; 
	
	P = new PetriNet;
	
	P->instantiate();
	
	
	P->display();
	
	return 0;
}

