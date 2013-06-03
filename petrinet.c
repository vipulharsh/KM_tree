#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "petrinet.h"




/*
 * I/O functions for Petri nets.
 */
int
petrinet_read(net **PN, FILE *stream)
{
	
	
	assert(stream != NULL);
	
	PN = malloc(sizeof(net));
	PN->init = marking_create();
	
	
	unsigned int nOfPlaces;
	fscanf(stream , "%d" , &nOfPlaces);
	
	marking_initialize(nOfPlaces);
	
	fscanf(stream , "%d" , &PN->trans_count);
	
	PN->trans = malloc(PN->trans_count * sizeof(transition));
	
	
	int trans_count= PN->trans_count;
	
	for(int 
	
	for(i = 0 ; i<dimension ;i++)
	{
		assert(!feof (stream));
		fscanf (stream, "%lf", &token);
		m[i]= token;
	}    
	return 1;
	
	
}


int		 petrinet_write(const net *PN, FILE *stream) //#to be done
{
	
	
	
	return 1;
}
