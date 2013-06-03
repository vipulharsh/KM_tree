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
#include "wint.h"

	
typedef double wint;   //since double can handle exact infinity

class marking{
	
	
	
public:
  
   
   
   vector<wint> tokens;
	
   static int nOfPlaces;      //the length of the tuple , defined in the marking.cpp file 
  
   marking(vector<wint> tokens1){}   //constructor, rarely used
  
   marking(){ tokens.resize(nOfPlaces);} 
   
   marking(int nOfPlaces1){
	   
	   nOfPlaces = nOfPlaces1 ; 
	   tokens.resize(nOfPlaces);
	   
   }
	   
  
   void input();
   
   
   void display();
    
/*
 *Define the comparison operators < , <= , == for markings  
 * 
 */    
    
   bool operator<=( const marking& other ) const;
   
   bool operator<( const marking& other ) const;
    
   bool operator==( const marking& other ) const;
    
   marking operator+( const marking& other ) const;
};   
   	














#endif
