#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "petrinet.h"




/*
 * I/O functions for Petri nets.
 */
int
petrinet_read(net **PNet, FILE *stream)
{
	
	
	assert(stream != NULL);
	
	
//Initialize dimension here	
	unsigned int nOfPlaces;
	fscanf(stream , "%d" , &nOfPlaces);
	marking_initialize(nOfPlaces);
	
	//printf("flag 3\n");
	
//allocate space to PNet	
	
	net *PN ;
	PN = malloc(sizeof(net));
	
	//printf("flag 4\n");
	
	
	PN->init = marking_create();
	
	//printf("flag 5\n");
	
	int trans_count;
		
	fscanf(stream , "%d" , &trans_count);
	PN->trans = malloc(trans_count * sizeof(transition));
	PN->trans_count = trans_count;
	
	
	//printf("flag 6\n   %d the number of transitions \n" , PN->trans_count);
	
	int i;
	for(i=0;i< PN->trans_count ; i++){
		
		PN->trans[i].input = marking_create();
		marking_read(PN->trans[i].input , stream);
		
		PN->trans[i].output = marking_create();
		marking_read(PN->trans[i].output , stream);		 
	}
	
	
	marking_read(PN->init , stream);
	//PNet = malloc(sizeof(net *));
	*PNet = PN;
	printf("PNet->transcount = %d \n", (*PNet)->trans_count);    
	return 1;
	
	
}


int		 petrinet_write(const net *PN, FILE *stream) 
{
	
	assert(stream != NULL);
	
	fprintf(stream , "No of transitions : %d \n", PN->trans_count);
	fprintf(stream , "No of Places : %d \n\n", dimension);
	
	
	int i;
	for(i=0;i< PN->trans_count ; i++)
	{
		fprintf(stream , "Transition number %d :\n" , i);
		marking_write(PN->trans[i].input , stream);
		fprintf(stream ,"\n");
		marking_write(PN->trans[i].output , stream);
		fprintf(stream ,"\n");
	}
	
	return 1;

}