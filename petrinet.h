#ifndef _KMT_PETRINET_H
#define _KMT_PETRINET_H

#include <stdio.h>

#include "marking.h"

/*
 * A marking is an array of length dimension whose elements are wnats.
 */

/*
 * transition: Petri net transition.
 */
typedef struct {
	wnat		*input;		/* marking */
	wnat		*output;	/* marking */
	char		*name;
} transition;

/*
 * net: Petri net.
 */
typedef struct {
	wnat		*init;		/* marking */
	transition	*trans;		/* array of length trans_count */
	unsigned int	 trans_count;
} net;

/*
 * I/O functions for Petri nets.
 */
int		 petrinet_read(FILE *stream, net **);
int		 petrinet_write(FILE *stream, const net *);

#endif	/* !_KMT_PETRINET_H */
