#include "PetriNet.h"
#include <iostream>
using namespace std;





void PetriNet :: instantiate (){
	cout<<"hello there" <<endl;

	cin >> nOfPlaces >> nOfTransitions ;


	transition t;
	
	marking::nOfPlaces = nOfPlaces;
	
	marking m;

	for (int i=0 ; i<nOfTransitions ;i++){

		m.input();
		t.assignReqMarking(m);
		m.input();
		t.assignTransitionVec(m);

		transitions.push_back(t);

	}
	
	//m.input();
	//initialMarking.nOfPlaces = nOfPlaces;   : not needed now , nOfPlaces is a static variable now
	
	initialMarking = new marking;
	
	
	initialMarking->tokens.resize(nOfPlaces);
	
    initialMarking->input();
	cout<<"jfdkj"<<endl;
	initialMarking->display();
	
}




PetriNet :: PetriNet (){
}




void PetriNet :: display(){
 cout<<"No of Places : "<< nOfPlaces <<endl;
 cout<<"No of Transitions : "<< nOfTransitions <<endl; 	

 for(int i=0; i<nOfTransitions; i++)
 {
	 
	 cout<<endl<<endl;
	 cout<<"Transition no "<<i<<"  :  "<<endl;
 	 transitions[i].display();
 	 cout<<endl<<endl;
	
}

 
 cout<<"Initial Marking  : ";
 initialMarking->display();
}



pair< list<marking*>::const_iterator, list<marking*>::const_iterator> PetriNet::reachableMarkings(marking* m){
	list<marking*>* markings;
	
	markings = new list<marking*>;
	
	
	marking* tempPointer;
	
	for (int i=0; i< nOfTransitions ; i++)
	{
		
		if(transitions[i].req <= *m){
			
			//m.display();
			//cout<<endl;
			//transitions[i].vec.display();
			//cout<<endl;
			
			tempPointer = new marking;
			*tempPointer = *m+transitions[i].vec ;
			markings->push_back(tempPointer);
		}
	}
	pair< list<marking*>::const_iterator, list<marking*>::const_iterator> p;
	
	p.first = markings->begin();
	p.second  = markings->end();



	return p;
	
}










