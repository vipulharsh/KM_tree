#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <inttypes.h>

#include "collection.h"
#include "petrinet.h"

void
petrinet_destroy(net *pn)
{
	unsigned int i;

	if (pn != NULL) {
		if (pn->place != NULL) {
			for (i = 0; i < pn->place_count; i++) {
				free(pn->place[i].name);
			}
		}
		free(pn->place);
		if (pn->trans != NULL) {
			for (i = 0; i < pn->trans_count; i++) {
				marking_destroy(pn->trans[i].input);
				marking_destroy(pn->trans[i].output);
				free(pn->trans[i].name);
			}
		}
		free(pn->trans);
		marking_destroy(pn->init);
	}
	free(pn);
}

/*
 * Stream I/O functions for Petri nets.
 */

int
petrinet_read_in(FILE *stream, net **PNet)
{
	net *PN;
	intmax_t pc, tc;
	unsigned int i;
	int res, errsv;

	assert(stream != NULL);
	res = 0;

	PN = malloc(sizeof(*PN));
	if (PN == NULL) {
		goto fail;
	}
	memset(PN, 0, sizeof(*PN));

	if ((res = fscanf(stream, "%jd", &pc)) < 1)
		goto fail;
	if ((res = fscanf(stream, "%jd", &tc)) < 1)
		goto fail;

	PN->place_count = (unsigned int)pc;
	PN->trans_count = (unsigned int)tc;

	/* Check for overflow. */
	if (pc != PN->place_count || tc != PN->trans_count)
		goto fail;

	/* Allocate and zeroify the arrays for places and transitions. */
	PN->place = malloc(PN->place_count * sizeof(place));
	if (PN->place == NULL) {
		goto fail;
	}
	memset(PN->place, 0, PN->place_count * sizeof(place));
	PN->trans = malloc(PN->trans_count * sizeof(transition));
	if (PN->trans == NULL) {
		goto fail;
	}
	memset(PN->trans, 0, PN->trans_count * sizeof(transition));

	/* Initialize dimension. */
	marking_initialize(PN->place_count);

	for (i = 0; i < PN->trans_count; i++) {
		if ((res = marking_read(stream, &PN->trans[i].input)) < 0)
			goto fail;
		if ((res = marking_read(stream, &PN->trans[i].output)) < 0)
			goto fail;
	}

	if ((res = marking_read(stream, &PN->init)) < 0)
		goto fail;

	*PNet = PN;
	return 0;

fail:
	errsv = errno;
	petrinet_destroy(PN);
	errno = errsv;
	return (res < 0) ? res : -1;
}





//returns index corresponding to pch(name of place), the position in the list
static
int returnIndex(char *pch , void *places_list , int place_count){
	
	int ind=0;
	
	void *temp = list_manager.create();
	while(!list_manager.empty(places_list)){
		char* m = list_manager.get(places_list);
		list_manager.put(temp , m);
		if(strcmp(m , pch) == 0){
			while(!list_manager.empty(temp)){
		     list_manager.put(places_list , list_manager.get(temp));
		  }
		  list_manager.destroy(temp);
		  return (place_count - ind) - 1;
		}
		else ind++; 
	}
   while(!list_manager.empty(temp)){
		     list_manager.put(places_list , list_manager.get(temp));
		  }
	list_manager.destroy(temp);	  
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
		  list_manager.destroy(temp);
		  return 0;
	    }
	 }


   while(!list_manager.empty(temp)){
		     list_manager.put(places_list , list_manager.get(temp));
		  }
   list_manager.destroy(temp);
   return 1;		  
}



static
long int returnAmt(char *s){
	
	
	
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
* 5 : having read once , analyse transition input
* 6: having read once , analyse transition output
*/ 
int		 petrinet_read_net(FILE *fp, net **PNet){
	int trans_count=0;
	int place_count=0;
	char c;
	int state=0;
	void *places_list = list_manager.create();
	int i;
	
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
	PN->place = NULL;
	PN->place_count = place_count;
	
	unsigned int h,d;
	for(d=0; d < dimension; d++){
		 	PN->init[d] = 0;
	}
	
	
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
				
				
				
				if(state==1){
					PN->trans[trans_number].name = malloc(strlen(so)+1);
					strcpy(PN->trans[trans_number].name , so);
					state=9;
					so = strtok (NULL, " ");
					continue;
				}
			
				
				
				
				
				
				
				
				
				if(state==5){
					int span = strcspn(so , "*");
					char *pch =  malloc(span+1);
					char *amt = malloc(strlen(so) - span+1);
					strncpy(pch , so , span);
					strncpy(amt , so + span, strlen(so)-span);
					int pl_number = returnIndex(pch , places_list , place_count);
					long int tokens = returnAmt(amt);
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
					int pl_number = returnIndex(pch , places_list , place_count);
					long int tokens = returnAmt(amt);
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
		
		
		
		if(state == 3 && c=='p'){
			if((c = fgetc(fp))=='l'){
				state = 7;
			}
		}
		
		if(state == 7){
			//read entire place
			i=0;
			char *entPlace = malloc(100);
			while((c = fgetc(fp))!='\n'){
			   entPlace[(i++)] = c;
			}
			int place_number;
			int amt;
			char *so;
			so = strtok (entPlace," ");
			while(so!=NULL){
				//printf(" so : %s \n" , so);
				if(so[0] == '('){
					char *temp = malloc(strlen(so)-2);
					strncpy(temp , so+1 , strlen(so)-2);
					amt = returnAmt(temp);
				//	printf("temp : %s \n" , temp); 
				 }
				else{
					place_number = returnIndex(so , places_list,place_count);
				}
				 so = strtok (NULL, " ");
			}
			printf("pl no: %d  and amt %d \n" , place_number , amt);
			PN->init[place_number] = amt;
			state = 3;
		}
		
		
		
		
		
	}//end of reading file twice
	
	
   *PNet = PN; 
	list_manager.destroy(places_list);		
return 1;
}



















int
petrinet_write(FILE *stream, const net *PN)
{
	unsigned int i;

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
