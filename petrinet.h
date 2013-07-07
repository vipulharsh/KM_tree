#ifndef _KMT_PETRINET_H
#define _KMT_PETRINET_H

#include <stdio.h>

#include "marking.h"

/*
 * A marking is an array of length dimension whose elements are wnats.
 */

/*
 * place: Petri net place.
 */
typedef struct {
	char		*name;
} place;

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
	place		*place;		/* array of length place_count */
	unsigned int	 place_count;
	transition	*trans;		/* array of length trans_count */
	unsigned int	 trans_count;
	wnat		*init;		/* marking */
} net;

void		 petrinet_destroy(net *);

/*
 * Stream I/O functions for Petri nets:
 *
 *	These functions return zero on success.  On error, a negative value
 *	is returned, and the pointer argument is left untouched.
 *
 *	Memory is allocated by the read functions to store the net.  The
 *	caller should subsequently destroy it when it is no longer needed.
 *
 *	The read functions call marking_initialize with a dimension that is
 *	equal to the Petri net's place count.
 */
int		 petrinet_read_in(FILE *, net **);
int		 petrinet_read_net(FILE *, net **);
int		 petrinet_write(FILE *, const net *);

#endif	/* !_KMT_PETRINET_H */
