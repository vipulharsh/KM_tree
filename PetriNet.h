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
	  
  std::list<marking> reachableMarkings(marking m);	  
  
  marking getInitialMarking(){
	  return initialMarking ;
  }
  
};	



#endif
