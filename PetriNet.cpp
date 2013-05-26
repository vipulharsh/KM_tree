#include "PetriNet.h"
#include <iostream>
using namespace std;





void PetriNet :: instantiate (){
	cout<<"hello there" <<endl;

	cin >> nOfPlaces >> nOfTransitions ;


	transition t;
	marking m(nOfPlaces);

	for (int i=0 ; i<nOfPlaces ;i++){

		m.input();
		t.assignReqMarking(m);
		m.input();
		t.assignTransitionVec(m);

		transitions.push_back(t);

	}
	
	m.input();
	
	initialMarking = m;
	
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
 initialMarking.display();
}














