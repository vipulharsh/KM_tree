#include <assert.h>
#include <stdlib.h>

#include "marking.h"

/* The global variable that stores the number of places. */
unsigned int dimension = 0;

void
marking_initialize(unsigned int d)
{
	/* Can be initialized only once. */
	assert(dimension == 0 && d > 0);
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
marking_read(FILE *stream, wnat **x)
{
	wnat *y;
	unsigned int i;
	int res;

	assert(dimension > 0);
	assert(stream != NULL);

	y = marking_create();
	if (y == NULL)
		return -1;

	for (i = 0; i < dimension; i++) {
		if ((res = wnat_read(stream, &y[i])) < 0)
			return res;
	}

	*x = y;
	return 0;
}

int
marking_write(FILE *stream, const wnat *x)
{
	unsigned int i;
	int res;

	assert(dimension > 0);
	assert(stream != NULL);

	if ((res = fprintf(stream, "(")) < 1)
		return (res < 0) ? res : -1;

	for (i = 0; i < dimension-1; i++) {
		if ((res = wnat_write(stream, x[i])) < 0)
			return res;
		if ((res = fprintf(stream, ",")) < 1)
			return (res < 0) ? res : -1;
	}

	if ((res = wnat_write(stream, x[i])) < 0)
		return res;
	if ((res = fprintf(stream, ")")) < 1)
		return (res < 0) ? res : -1;

	return 0;
}
