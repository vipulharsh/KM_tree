#include <assert.h>
#include <stdlib.h>
#include "marking.h"

unsigned int dimension = 0;

void
marking_initialize(unsigned int d)
{
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
