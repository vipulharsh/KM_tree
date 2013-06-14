#ifndef __wint_H
#define __wint_H


struct Wint{
	unsigned long int val;
	bool omega;
 	
	
	
	
	
	
    bool operator<( const Wint& other ) const{
	  if(omega) return false;
	  
	  if(other.omega) return true;
	  
	  return (val < other.val);
	}
   
   
  
    bool operator<=( const Wint& other ) const{
	  if(other.omega) return true;
	  
	  if(omega) return false;
	  
	  return (val <= other.val);
	}
   
   
   
   
   
   
   
   
   
   
   bool operator>( const Wint& other ) const{
	  if(other.omega) return false;
	  
	  if(omega) return true;
	  
	  return (val > other.val);
	}
   
   
   bool operator>=( const Wint& other ) const{
	  if(omega) return true;
	  
	  if(other.omega) return false;
	  
	  return (val >= other.val);
	}
   
   
   
   bool operator==( const Wint& other ) const{
	  if(omega == other.omega) return true;
	  
	  return (val == other.val);
	}
   
   
   
   
   
   
   
   
};







#endif

