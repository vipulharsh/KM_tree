#ifndef __marking_H
#define __marking_H


#include <iostream>
using namespace std;
#include <sstream>
//#include <list>
#include <vector>
#include <string>
#include <limits>
#include <stdio.h>
#include <stdlib.h>

	
typedef double wint;   //omega int

class marking{
	
	
	
public:
  
   
   
   vector<wint> tokens;
	
	int nOfPlaces;
   
   
   
   marking(vector<wint> tokens1){}   //constructor
   marking(){}
   
   marking(int nOfPlaces1){
	   
	   nOfPlaces = nOfPlaces1 ; 
	   tokens.resize(nOfPlaces);
	   
   }
	   
  
   
   
   
   
   
   void input()
   {
	  
	  string s;
	  for(int i=0; i<nOfPlaces; i++){
		cin>>s;

	    if(s=="w")
	     tokens[i] = numeric_limits<double>::infinity();
		else {
		//cout << atoi(s.);
		 istringstream convert(s);
		 if ( ! (istringstream(s) >> tokens[i]) ) tokens[i] = 0;
		}
	 } //end for	
 
   }
   
   
   
   void display(){
	   cout<< " (";
	    
	   int i; 
	   for (i=0; i<nOfPlaces-1; i++)
		   cout<<tokens[i]<<",";
		
	   cout <<tokens[i]<<") ";
   }	   
    
    
    
    
    
    
   bool operator<=( const marking& other ) const{
	   if(nOfPlaces != other.nOfPlaces) return false;
	   
	   bool res=true;
	   
	   for(int i=0; i<nOfPlaces && res; i++){
		   res  &= (tokens[i] <= other.tokens[i]);		   
	   }
	   
	   return res;
	   
   }
    
    
    
  marking operator+( const marking& other ) const{
	   
	   marking m;
	   
	   m.tokens.resize(nOfPlaces);
	   m.nOfPlaces = nOfPlaces;
	   
	   for(int i=0; i<nOfPlaces; i++){
		   m.tokens[i] = (tokens[i] + other.tokens[i]);		   
	   }
	   
	   return m;
	   
   }  
    
    
    
    
    
   
};   
   	














#endif
