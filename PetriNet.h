#ifndef __PN_H
#define __PN_H



#include <list>
#include "place.h"
#include "transition.h"
#include "marking.h"
#include <vector>


class PetriNet{
	
	int nOfPlaces ;
	
	int nOfTransitions ;
	
	//std::vector<place> places ;
	
	std::vector<transition> transitions ;
	
	marking initialMarking ;
	
	
	

public:


  void display();
  
  int getNofPlaces(){
	 return nOfPlaces;
  }
  
  
  PetriNet();
  
  void instantiate();
	  
  
  
   //markings reachable from m in 1 step
  pair< list<marking>::const_iterator, list<marking>::const_iterator> reachableMarkings(marking m);
  
  
  marking getInitialMarking(){
	  return initialMarking ;
  }
  
};	



#endif
