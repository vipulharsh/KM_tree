#include "marking.h"




int marking::nOfPlaces;



   void marking::input()
   {
	  
	  string s;
	  for(int i=0; i<nOfPlaces; i++){
		cin>>s;

	    if(s=="w")
	     //tokens[i].omega = true;
	     tokens[i] = numeric_limits<double>::infinity(); 
	     
	    //numeric_limits<double>::infinity() is the exact infinity 
		else {
		 istringstream convert(s);
		 if ( ! (istringstream(s) >> tokens[i]) ) tokens[i] = 0;
		}
	 } //end for	
 
   }//end of input
   
   
   



  void marking::display(){
	   cout<< " (";
	    
	   int i; 
	   for (i=0; i<nOfPlaces-1; i++)
		   cout<<tokens[i]<<",";
		
	   cout <<tokens[i]<<") ";
   }	   
    
   




  bool marking::operator<=( const marking& other ) const{
	   if(nOfPlaces != other.nOfPlaces) return false;
	   
	   bool res=true;
	   
	   for(int i=0; i<nOfPlaces && res; i++){
		   res  &= (tokens[i] <= other.tokens[i]);		   
	   }
	   
	   return res;
	   
   }
    
    
    
    bool marking::operator<( const marking& other ) const{
	   if(nOfPlaces != other.nOfPlaces) return false;
	   
	   bool res=true;
	   int eq = 0;
	   
	   for(int i=0; i<nOfPlaces && res; i++){
		   res  &= (tokens[i] <= other.tokens[i]);
		   if(tokens[i] == other.tokens[i])	eq++;	   
	   }

	   return (res && (eq != nOfPlaces));
	   
   }
    
    
   bool marking::operator==( const marking& other ) const{
	   if(nOfPlaces != other.nOfPlaces) return false;
	   
	   bool res=true;
	   
	   for(int i=0; i<nOfPlaces && res; i++){
		   res  &= (tokens[i] == other.tokens[i]);		   
	   }
	   
	   return res;
	   
   }
    
    
    
    
    
    
  marking marking::operator+( const marking& other ) const{
	   
	   marking m;
	   
	   m.tokens.resize(nOfPlaces);
	   m.nOfPlaces = nOfPlaces;
	   
	   for(int i=0; i<nOfPlaces; i++){
		   m.tokens[i] = (tokens[i] + other.tokens[i]);		   
	   }
	   
	   return m;
	   
   }  
 
