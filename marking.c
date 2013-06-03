#include <assert.h>
#include <stdlib.h>
#include "marking.h"

unsigned int dimension = 0; //The Global Variable to store the number of places

void
marking_initialize(unsigned int d)
{
	assert(dimension == 0 && d > 0);  //can be initialized only once
	dimension = d;
}

wnat *
marking_create(void)
{
	    assert(dimension > 0);
        return malloc(dimension * sizeof(wnat));
}

void
marking_destroy(wnat *x)
{
	free(x);
}



int
marking_eq(const wnat *m1, const wnat *m2)
{
	int result = 1;
	assert(dimension > 0);
	int i;
	for(i=0;i<dimension ; i++)
		if(!wnat_eq(m1[i] , m2[i])){
			result = 0;
			break;
		}
	return result;
	
}





int
marking_le(const wnat *m1, const wnat *m2){
	int result = 1;
	assert(dimension > 0);
	int i;
	for(i=0;i<dimension ; i++)
		if(!wnat_leq(m1[i] , m2[i])){
			result = 0;
			break;
		}
	return result & (marking_eq(m1,m2));   //NOTE : marking_eq is an inline function

}







int
marking_leq(const wnat *m1, const wnat *m2){
	int result = 1;
	assert(dimension > 0);
	int i;
	for(i=0;i<dimension ; i++)
		if(!wnat_leq(m1[i] , m2[i])){
			result = 0;
			break;
		}
	return result;
}







void
marking_add(wnat *m1, const wnat *m2, const wnat *m3)   //might have to remove const from the 3rd argument
{
	assert(dimension > 0);
	int i;
	for(i=0;i<dimension ; i++)
		m1[i] = wnat_add(m2[i] , m3[i]);	
}






void
marking_sub(wnat *m1, const wnat *m2, const wnat *m3)  //might have to remove const from the 3rd argument
{
	assert(dimension > 0);
	assert(marking_leq(m2,m3));
	int i;
	for(i=0;i<dimension ; i++)
		m1[i] = wnat_sub(m2[i] , m3[i]);
}




int
marking_read(wnat *m, FILE *stream)
{
	
	assert(stream != NULL);
	
	double token;
	int i;
	for(i = 0 ; i<dimension ;i++)
	{
		assert(!feof (stream));
		fscanf (stream, "%lf", &token);
		m[i]= token;
	}    
	return 1;
}




int
marking_write(const wnat *m, FILE *stream)
{
	
	assert(stream != NULL);
	
	fprintf(stream , "(");
	int i;
	for(i = 0 ; i<dimension ;i++)
	{
		fprintf (stream, "%lf,", m[i]);
	}
	fprintf(stream , ")");    
	return 1;
	
}






