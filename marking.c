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
	
	assert(dimension > 0);
	int i;
	for(i=0;i<dimension ; i++){
		
		//printf("  %lf %lf | ",m1[i] ,m2[i]); 
		if(!wnat_eq(m1[i] , m2[i])){
			return 0;
		}
	}
		
		
	return 1;
	
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
	return result & (!marking_eq(m1,m2));   //NOTE : marking_eq is an inline function

}







int
marking_leq(const wnat *m1, const wnat *m2){
	int result = 1;
	assert(dimension > 0);
	int i;
	for(i=0;i<dimension ; i++){
		if(!wnat_leq(m1[i] , m2[i])){
			result = 0;
			break;
		}
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
marking_sub(wnat *m1, const wnat *m2, const wnat *m3) 
{
	assert(dimension > 0);
	assert(marking_leq(m3,m2));
	int i;
	for(i=0;i<dimension ; i++)
		m1[i] = wnat_sub(m2[i] , m3[i]);
}




int
marking_read(FILE *stream, wnat *m)
{
	int i;

	assert(stream != NULL);

	for(i = 0; i < dimension; i++) {
		assert(!feof(stream));		/* XXX */
		fscanf(stream, "%lf", &m[i]);
	}
	return 1;
}

int
marking_write(FILE *stream, const wnat *m)
{
	int i;

	assert(stream != NULL);

	fprintf(stream , "(");
	for(i = 0; i < dimension-1; i++)
	{
		fprintf(stream, "%.0lf,", m[i]);
	}

	fprintf(stream, "%.0lf)", m[i]);
	return 1;
}
