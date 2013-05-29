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

	
	
	
	
	kmTree t(P);
    
    
    
    node *km = t.expand();
    

	
	cout<<endl<<endl<<"The tree"<<endl;
	
	
   list<pair<node *,int> > var;
   
   pair<node* , int> p;
   p.first = km;
   p.second =0;
   var.push_back(p);
  
  
   cout<<"DONE !"<<endl;
   
   int t1;
   
   while(!var.empty()){
	   node *a= var.front().first;
	   t1  = var.front().second;
	   var.pop_front();
	   a->label.display();
	   
	   if(a->parent != NULL) {
		   cout<<" : of parent";
		   a->parent->label.display();
		   cout<<" : at level "<<t1<<endl;
	   }
	    
	   list<node *>::const_iterator iterator;
	   for (iterator = a->children.begin(); iterator != a->children.end(); ++iterator) {    
          p.first = *iterator ;
          p.second = t1+1 ;
          var.push_back(p);
        }
	}
	
	
	cout<<"level of tree is : "<<t1<<endl;
	
	
	
	
	
	return 0;
}

