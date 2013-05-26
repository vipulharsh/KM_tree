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
  
  PetriNet();
  
  void instantiate();
	  
  std::list<transition> firableTransitions(marking m);	  
};	



#endif
