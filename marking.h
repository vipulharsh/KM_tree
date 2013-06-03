#ifndef _KMT_MARKING_H
#define _KMT_MARKING_H

#include <stdio.h>
#include "wnat.h"

/*
 * dimension:
 *
 *	This global variable is assigned when the Petri net is read from the
 *	standard input, and remains constant afterwards.
 */
extern unsigned int	 dimension;

void		marking_initialize(unsigned int d);

/*
 * A marking is an array of length dimension whose elements are wnats.
 */

/*
 * Important note on memory management:
 *
 *	Apart from marking_create, none of the following functions allocate
 *	memory.  The perform in-place modifications.
 */

wnat		*marking_create(void);
void		marking_destroy(wnat *);

/*
 * XXX	The following should be defined static inline.  Implement them!
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
void		marking_copy(wnat *, const wnat *);
int		marking_eq(const wnat *, const wnat *);
int		marking_le(const wnat *, const wnat *);
int		marking_leq(const wnat *, const wnat *);
void		marking_add(wnat *, const wnat *, const wnat *);
void		marking_sub(wnat *, const wnat *, const wnat *);

/*
 * I/O functions for markings.
 */
int		marking_read(wnat *, FILE *stream);
int		marking_write(const wnat *, FILE *stream);

#endif	/* !_KMT_MARKING_H */
