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
