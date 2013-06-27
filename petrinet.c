#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "petrinet.h"




/*
 * I/O functions for Petri nets.
 */
int
petrinet_read(FILE *stream, net **PNet)
{
	unsigned int nOfPlaces;

	assert(stream != NULL);


//Initialize dimension here
	fscanf(stream , "%d" , &nOfPlaces);
	marking_initialize(nOfPlaces);
		
//allocate space to PNet	
	
	net *PN ;
	PN = malloc(sizeof(net));
	
	
	PN->init = marking_create();
	
	
	int trans_count;
		
	fscanf(stream , "%d" , &trans_count);
	PN->trans = malloc(trans_count * sizeof(transition));
	PN->trans_count = trans_count;
	
	
	int i;
	for(i=0;i< PN->trans_count ; i++){
		
		PN->trans[i].input = marking_create();
		marking_read(stream, PN->trans[i].input);
		
		PN->trans[i].output = marking_create();
		marking_read(stream, PN->trans[i].output);
	}
	
	
	marking_read(stream, PN->init);
	//PNet = malloc(sizeof(net *));
	*PNet = PN;
	printf("PNet->transcount = %d \n", (*PNet)->trans_count);    
	return 1;
	
}






static
int returnIndex(char *pch , void *places_list){
	
	int ind=0;
	
	void *temp = list_manager.create();
	while(!list_manager.empty(places_list)){
		char* m = list_manager.get(places_list);
		list_manager.put(temp , m);
		if(strcmp(m , pch) == 0){
			while(!list_manager.empty(temp)){
		     list_manager.put(places_list , list_manager.get(temp));
		  }
		  return ind;
		}
		else ind++; 
	}
   while(!list_manager.empty(temp)){
		     list_manager.put(places_list , list_manager.get(temp));
		  }
	return -1;
	
}





static
int notPresent(char *pch , void *places_list){
	
	void *temp = list_manager.create();
	while(!list_manager.empty(places_list)){
	    char* m = list_manager.get(places_list);
		list_manager.put(temp , m);
		if(strcmp(m , pch) == 0){
		  while(!list_manager.empty(temp)){
		     list_manager.put(places_list , list_manager.get(temp));
		  }
		  return 0;
	    }
	 }


   while(!list_manager.empty(temp)){
		     list_manager.put(places_list , list_manager.get(temp));
		  }
   return 1;		  
}



static
long int returnAmt(char *s){
	
	
	printf("amt is %s \n",s);
	
	long int res=0;
	if(strcmp (s,"")==0) { res=1; return 1;}
	
	int digit,i;
	i=0;
	while(s[i]!='\0'){
		if(s[i] == 'K' || s[i] == 'k') { res = res * 1000; return res; }
		if(s[i] == 'M' || s[i] == 'm') { res = res * 1000000; return res; }
		if(s[i] == '*') { i++; continue; }
		//else
		digit  = s[i]-'0';
		res = res*10 + digit;
		i++;
	}
	
	return res;
	
}





/*
 state
* 0 : initial gargbage 
* 1 : gotta read a transition
* 2 : reading input/output places of a transition
* 3 : finished reading a transition
*/ 
int		 petrinet_read1(FILE *fp, net **PNet){
	int trans_count=0;
	int place_count=0;
	char c;
	int state=0;
	void *places_list = list_manager.create();
	int i,j,k,l;
	
	while((c = fgetc(fp))!=EOF){
		if(state==0){            //remove initial garbage
			if(c == 't'){
				c = fgetc(fp);
				if(c == 'r') state=1;
			}
			else continue;
		}//end of state 0
		
		if(state == 1 && (c == ' ' || c == '\t' || c=='\n')){
		//read entire transition
			
			trans_count++;
			i=0;
			char *entTrans = malloc(100);
			while((c = fgetc(fp))!='\n'){
			   entTrans[(i++)] = c;
			}
			
					
			char *so;
			so = strtok (entTrans," ");
 		    while (so != NULL)
			{
				
				if(so[0]=='['||so[0]=='-'){
				 state=2;	
				 so = strtok (NULL, " ");
				 continue;
			    }
				
				if(state==2){
					int span = strcspn(so , "*");
					char *pch =  malloc(span+1);
					strncpy(pch , so , span);
					if(notPresent(pch , places_list)){
						char *placeName = malloc(strlen(pch) + 1);
						strcpy(placeName , pch);
						list_manager.put(places_list , placeName);
						place_count++;
					}
					
				 so = strtok (NULL, " ");	
				 continue;
			      }	
				
				so = strtok (NULL, " ");
				 
			}
			state=3;
		}//end of state 1
		
		if(state == 3 && c=='t'){
			if((c = fgetc(fp))=='r'){
				state = 1;
			}
			continue;
		}
	}//end of reading file once
	
	printf("no of places %d , no' of transitions %d \n" , place_count , trans_count);
	
	
	
	marking_initialize(place_count);
	
	net *PN;
	PN = malloc(sizeof(net));
	PN->init = marking_create();
	PN->trans = malloc(trans_count * sizeof(transition));
	PN->trans_count = trans_count;
	
	int h,d;
	for(h=0; h < PN->trans_count ; h++){
		PN->trans[h].input = marking_create();
		PN->trans[h].output = marking_create();
		for(d=0; d < dimension; d++){
		 	PN->trans[h].input[d] = 0;
			PN->trans[h].output[d] = 0;
		}
	}
	
	rewind(fp);
	state=0;
	int trans_number=-1;
	while((c = fgetc(fp))!=EOF){
		if(state==0){            //remove initial garbage
			if(c == 't'){
				c = fgetc(fp);
				if(c == 'r') state=1;
			}
			else continue;
		}//end of state 0
		
		if(state == 1 && (c == ' ' || c == '\t' || c=='\n')){
		//read entire transition
		
		 printf("\n New Transition **** \n");
		
			trans_number++;
			i=0;
			char *entTrans = malloc(100);
			while((c = fgetc(fp))!='\n'){
			   entTrans[(i++)] = c;
			}
			
			char *so;
			so = strtok (entTrans," ");
 		    while (so != NULL)
			{
				
				
			//	printf("here %s %d \n",so,state);
				
				
				if(so[0]=='['){
				 state=5;	
				 so = strtok (NULL, " ");
				 continue;
			    }
			    
			    if(so[0]=='-'){
				 state=6;	
				 so = strtok (NULL, " ");
				 continue;
			    }
				
				if(state==5){
					int span = strcspn(so , "*");
					char *pch =  malloc(span+1);
					char *amt = malloc(strlen(so) - span+1);
					strncpy(pch , so , span);
					strncpy(amt , so + span, strlen(so)-span);
					int pl_number = returnIndex(pch , places_list);
					long int tokens = returnAmt(amt);
					printf("Input :first %s , second %s %d %d\n" , pch , amt, strlen(amt),tokens);
					PN->trans[trans_number].input[pl_number] = tokens;
				 so = strtok (NULL, " ");	
				 continue;
			     }
			     
			    if(state==6){
					int span = strcspn(so , "*");
					char *pch =  malloc(span+1);
					char *amt = malloc(strlen(so) - span+1);
					strncpy(pch , so , span);
					strncpy(amt , so + span, strlen(so)-span);
					int pl_number = returnIndex(pch , places_list);
					long int tokens = returnAmt(amt);
					printf("output :first %s , second %s %d %d\n" , pch , amt, strlen(amt),tokens);
					PN->trans[trans_number].output[pl_number] = tokens;
				 so = strtok (NULL, " ");	
				 continue;
			     } 
			     	
				
				so = strtok (NULL, " ");
				 
			}
			state=3;
		}//end of state 1
		
		if(state == 3 && c=='t'){
			if((c = fgetc(fp))=='r'){
				state = 1;
			}
			continue;
		}
	}//end of reading file twice
	
	printf("ho ja yaar \n");
	for(h=0; h< PN->trans_count ; h++){
		printf(" %d %d \n", h ,PN->trans_count);
		marking_write(stdout , PN->trans[h].input);
		marking_write(stdout , PN->trans[h].output);
		printf( "done \n\n");
	}

			
return 1;
}



















int
petrinet_write(FILE *stream, const net *PN)
{
	int i;

	assert(stream != NULL);

	fprintf(stream , "No of transitions : %d \n", PN->trans_count);
	fprintf(stream , "No of Places : %d \n\n", dimension);

	for(i=0;i< PN->trans_count ; i++)
	{
		fprintf(stream , "Transition number %d :\n" , i);
		marking_write(stream, PN->trans[i].input);
		fprintf(stream ,"\n");
		marking_write(stream, PN->trans[i].output);
		fprintf(stream ,"\n");
	}

	return 1;
}
