#ifndef __transition_H
#define __transition_H


#include "marking.h"

typedef  marking transition_vector ;


class transition{
	
	marking req;      //the minimum marking required such that this transition is firable
	
	
	transition_vector vec;  //the transition vector for the transition
	
	

public:
	
	transition(){};
	
	
	void assignReqMarking(marking m){
		
		req = m ;
		
		}
    void assignTransitionVec(marking m){
		vec = m;
		
		}
    
    
    void display(){
		cout<<"Minimum Marking is :";
		req.display();
		cout<<endl;
		cout<<"Transition Vector is :";
		vec.display();
		cout<<endl;

	}


};




#endif
