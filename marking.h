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
 * Arithmetic operations on markings.  These functions perform the following
 * pseudo-code operations:
 *
 *	marking_copy(x, y)		x := y
 *	marking_eq(x, y)		x == y
 *	marking_leq(x, y)		x <= y
 *	marking_le(x, y)		x < y
 *	marking_add(x, y, z)		x := y+z
 *	marking_sub(x, y, z)		x := y-z
 */
static inline void
marking_copy(wnat *x, const wnat *y)
{
	(void)memcpy(x, y, dimension * sizeof(wnat));
}

static inline int
marking_eq(const wnat *m1, const wnat *m2)
{
	unsigned int i;

	assert(dimension > 0);
	for (i = 0; i < dimension; i++) {
		if (!wnat_eq(m1[i], m2[i]))
			return 0;
	}
	return 1;
}

static inline int
marking_leq(const wnat *m1, const wnat *m2)
{
	unsigned int i;

	assert(dimension > 0);
	for (i = 0; i < dimension; i++) {
		if (!wnat_leq(m1[i], m2[i]))
			return 0;
	}
	return 1;
}

static inline int
marking_le(const wnat *m1, const wnat *m2)
{
	assert(dimension > 0);
	return (marking_leq(m1, m2) && (!marking_eq(m1, m2)));
}

static inline void
marking_add(wnat *m1, const wnat *m2, const wnat *m3)
{
	unsigned int i;

	assert(dimension > 0);
	for (i = 0; i < dimension; i++)
		m1[i] = wnat_add(m2[i], m3[i]);
}

static inline void
marking_sub(wnat *m1, const wnat *m2, const wnat *m3)
{
	unsigned int i;

	assert(dimension > 0);
	assert(marking_leq(m3, m2));
	for (i = 0; i < dimension; i++)
		m1[i] = wnat_sub(m2[i], m3[i]);
}

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
