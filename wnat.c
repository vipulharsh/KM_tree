#include <assert.h>
#include <stdio.h>

#include "wnat.h"

int
wnat_read(FILE *stream, wnat *x)
{
	wnat y;
	int res;

	res = fscanf(stream, "%lf", &y);
	if (res < 0)
		return res;
	else if (res == 0 || (!IS_WNAT(y)))
		return -1;
	*x = y;
	return 0;
}

int
wnat_write(FILE *stream, wnat x)
{
	int res;
	
//	printf("s:  %0.200lf ,  %d \n" ,x,trunc(x));

	assert(IS_WNAT(x));
	res = fprintf(stream, "%.0lf", x);
	if (res < 0)
		return res;
	else if (res == 0)
		return -1;
	return 0;
}
