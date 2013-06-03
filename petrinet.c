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
	
	PNet = malloc(sizeof(net));
	
	net *PN = *PNet;
	
	PN->init = marking_create();
	
	
	unsigned int nOfPlaces;
	fscanf(stream , "%d" , &nOfPlaces);
	
	marking_initialize(nOfPlaces);
	
	fscanf(stream , "%d" , &PN->trans_count);
	
	PN->trans = malloc(PN->trans_count * sizeof(transition));
	
	
	int trans_count= PN->trans_count;
	
	
	int i,j;
	double token;
	for(i=0;i< PN->trans_count ; i++){
		for(j = 0 ; j<dimension ;j++)
		{
			assert(!feof (stream));
			fscanf (stream, "%d", &(PN->trans[i].input[j]));
	    }
	    for(j = 0 ; j<dimension ;j++)
		{
			assert(!feof (stream));
			fscanf (stream, "%d", &(PN->trans[i].output[j]));
	    }
	}    
	return 1;
	
	
}


int		 petrinet_write(const net *PN, FILE *stream) //#to be done
{
	
	assert(stream != NULL);
	
	fprintf(stream , "No of transitions : %d \n", PN->trans_count);
	fprintf(stream , "No of Places : %d \n\n", dimension);
	
	int i,j;
	for(i=0;i< PN->trans_count ; i++){
		fprintf(stream , "Transition number %d :\n(" , i);
		for(j = 0 ; j<dimension-1 ;j++)
		{
			fprintf (stream, "%lf,", PN->trans[i].input[j]);
		}
		fprintf (stream, "%lf)\n", PN->trans[i].input[j]);
		for(j = 0 ; j<dimension-1 ;j++)
		{
			fprintf (stream, "%lf,", PN->trans[i].output[j]);
		}
		fprintf (stream, "%lf)\n", PN->trans[i].output[j]);
	}
	return 1;

}
