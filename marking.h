#ifndef _KMT_MARKING_H
#define _KMT_MARKING_H

#include <stdio.h>
#include <string.h>

#include "wnat.h"

/*
 * dimension:
 *
 *	This global variable is assigned when the Petri net is read from the
 *	input file, and remains constant afterwards.
 */
extern unsigned int	 dimension;

void		 marking_initialize(unsigned int);

/*
 * A marking is an array of length dimension whose elements are wnats.
 */

/*
 * Important note on memory management:
 *
 *	Apart from marking_create and marking_read, none of the following
 *	functions allocate memory.  They perform in-place modifications.
 */

wnat		*marking_create(void);
void		 marking_destroy(wnat *);

/*
 * XXX	The following should be defined static inline.
 */

/*
 * Arithmetic operations on markings.  These functions perform the following
 * pseudo-code operations:
 *
 *	marking_copy(x, y)		x := y
 *	marking_eq(x, y)		x == y
 *	marking_le(x, y)		x < y
 *	marking_leq(x, y)		x <= y
 *	marking_add(x, y, z)		x := y+z
 *	marking_sub(x, y, z)		x := y-z
 */
static inline void
marking_copy(wnat *x, const wnat *y)
{
	(void)memcpy(x, y, dimension * sizeof(wnat));
}



int		 marking_eq(const wnat *, const wnat *);
int		 marking_le(const wnat *, const wnat *);
int		 marking_leq(const wnat *, const wnat *);
void		 marking_add(wnat *, const wnat *, const wnat *);
void		 marking_sub(wnat *, const wnat *, const wnat *);

/*
 * Stream I/O functions for markings:
 *
 *	These functions return zero on success.  On error, a negative value
 *	is returned, and the pointer argument is left untouched.
 *
 *	Memory is allocated by the read functions to store the marking.  The
 *	caller should subsequently destroy it when it is no longer needed.
 */
int		 marking_read(FILE *, wnat **);
int		 marking_write(FILE *, const wnat *);

#endif	/* !_KMT_MARKING_H */
