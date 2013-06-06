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
	
	int i,j;
	double token;
	for(i=0;i< PN->trans_count ; i++){
		
		//printf("flag 8\n");
		
		PN->trans[i].input = marking_create();
		marking_read(PN->trans[i].input , stream);
		
		PN->trans[i].output = marking_create();
		marking_read(PN->trans[i].output , stream);		/*
		for(j = 0 ; j<dimension ;j++)
		{
			assert(!feof (stream));
			PN->trans[i].input = marking_create();
			fscanf (stream, "%lf", &(PN->trans[i].input[j]));
			printf(" %d %d \n",i,j);
	    }
	    for(j = 0 ; j<dimension ;j++)
		{
			assert(!feof (stream));
			PN->trans[i].output = marking_create();
			fscanf (stream, "%lf", &(PN->trans[i].output[j]));
			printf(" %d %d \n",i,j);
	    }
	    */ 
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
	
	//printf(" flag 7 \n");
	
	printf("No of transitions : %d \n", PN->trans_count);
	fprintf(stream , "No of transitions : %d \n", PN->trans_count);
	
	
	//printf(" flag 8 \n");
	
	printf("No of Places : %d \n\n", dimension);
	fprintf(stream , "No of Places : %d \n\n", dimension);
	
	//printf(" flag 9 \n");
	
	int i,j;
	for(i=0;i< PN->trans_count ; i++){
		fprintf(stream , "Transition number %d :\n" , i);
		
		marking_write(PN->trans[i].input , stream);
		
		fprintf(stream ,"\n");
		 
		 marking_write(PN->trans[i].output , stream);
		
		fprintf(stream ,"\n");
		
		/*
		for(j = 0 ; j<dimension-1 ;j++)
		{
			fprintf (stream, "%lu,", (unsigned long int)PN->trans[i].input[j]);
		} 
		fprintf (stream, "%lu)\n", PN->trans[i].input[j]);
		*/
		/*
		for(j = 0 ; j<dimension-1 ;j++)
		{
			fprintf (stream, "%lu,", PN->trans[i].output[j]);
		}
		fprintf (stream, "%lu)\n", PN->trans[i].output[j]);
		*/ 
	}
	return 1;

}
