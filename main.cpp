#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


#include "PetriNet.h"
#include "tree.h"
#include "wint.h"















void createDotFile(node *root){
	
	ofstream dotFile;
	dotFile.open("tree.dot");
	
	if (dotFile.is_open())
	{
		
		dotFile<<"digraph G { \n";
		
		
		dotFile<<"a->b\n";
		
		list<node*> unprocessedNodes;
		unprocessedNodes.push_back(root);
	
	
		string Result;          // string which will contain the result

		stringstream ss;
		string str = ss.str();    
	
		while(!unprocessedNodes.empty())
		{
	  
		node* temp = unprocessedNodes.front();
		unprocessedNodes.pop_front();
	  
	  
	    list<node *>::const_iterator iterator;
	    for (iterator = temp->children.begin(); iterator != temp->children.end(); ++iterator){     
			    unprocessedNodes.push_back(*iterator);
			    
			    
			    
			    
			    
			    ss.str(std::string());
				ss<<'(';
				int i;
				for (i=0; i<marking::nOfPlaces-1; i++){
					ss << (*iterator)->label->tokens[i]<<",";
				}
				ss << (*iterator)->label->tokens[i]<<")";
				Result = ss.str();
				dotFile <<*iterator<<" [label = "<<Result<<"];\n";
			    
			    
			    dotFile<<temp <<"->"<<*iterator<<";\n"; 
					
			    
/*				
			    dotFile<<"";
				int i;
				
				ss.str(std::string());
				
				ss<<'(';
				
				for (i=0; i<marking::nOfPlaces-1; i++){
					 ss << temp->label->tokens[i]<<","; 
				}
				ss << temp->label->tokens[i]<<")";
				Result = ss.str(); 
				dotFile <<Result<<"->";
*/				
				
        
        }
	  }
		
		dotFile<<"}";
		
		dotFile.close();
   }
	else cout << "Unable to open file";
	
}
























void printTree(node *root){
	list< pair<node* , int> > unprocessed;
	
	
	pair<node* ,int> dummy;
	
	dummy.first = root;
	dummy.second = 0;
	
	unprocessed.push_front(dummy);
	
	
	
	while(!unprocessed.empty()){
	  
	  pair<node* , int> p = unprocessed.front();
	  unprocessed.pop_front();
	  
	  
	  for(int i=0;i<p.second ; i++)
	     cout<<"   ";
	  p.first->label->display();
	  cout<<endl;
	  
	  
	  list<node*>::const_iterator iterator;
      for (iterator = p.first->children.begin(); iterator != p.first->children.end(); ++iterator){
		  
		  dummy.first = *iterator;
		  dummy.second  = p.second +1;
		  
		  unprocessed.push_front(dummy);     
		}
	}   
}




int main(){
	
	PetriNet *P; 
	
	P = new PetriNet;
	
	
	cout<<"0"<<endl;
	
	P->instantiate();
	
	cout<<"1"<<endl;
	
	P->display();
	
	
	/*
	list<marking> trying =  P->reachableMarkings(P->getInitialMarking());
	
	list<marking>::const_iterator iterator;
	
	cout<<endl<<"from here"<<endl;
	for (iterator = trying.begin(); iterator != trying.end(); ++iterator) {    
    marking temp = *iterator;
    
    temp.display();
    
    
    }
    */ 

	cout<<"1"<<endl;
	
	
	
	kmTree t(P);
    
    
    
    
    node *km = t.expand();
    

	
	cout<<endl<<endl<<"The tree"<<endl;
	
	
   list<pair<node *,int> > var;
   
   pair<node* , int> p;
   p.first = km;
   p.second =0;
   var.push_back(p);
  
  
   cout<<"DONE !"<<endl;
   
   

/*
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
*/


    printTree(km);
    	
	
	createDotFile(km);
	
	
	
	return 0;
}

