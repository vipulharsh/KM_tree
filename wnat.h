#ifndef _KMT_WNAT_H
#define _KMT_WNAT_H

#include <assert.h>
#include <math.h>

/*
 * wnat: Natural number or omega.
 *
 * XXX	Rework this.
 */
typedef	double		 wnat;

/*
 * omega: The value of type wnat that represents omega.
 */
static const wnat omega = INFINITY;

/* Macro to check that a double is a wnat.  Only used in assertions. */
#define IS_WNAT(x)	(x == trunc(x))

/*
 * wnat_from: Converts an unsigned int into a wnat.
 */
static inline wnat
wnat_from(unsigned int n)
{
	return (wnat)n;
}

/*
 * Arithmetic operations on wnats.
 */
static inline int
wnat_eq(wnat x, wnat n)
{
	assert(IS_WNAT(x) && IS_WNAT(n));
	return x == n;
}

static inline int
wnat_le(wnat x, wnat n)
{
	assert(IS_WNAT(x) && IS_WNAT(n));
	return x < n;
}

static inline int
wnat_leq(wnat x, wnat n)
{
	assert(IS_WNAT(x) && IS_WNAT(n));
	return x <= n;
}

static inline wnat
wnat_add(wnat x, wnat n)
{
	assert(IS_WNAT(x) && IS_WNAT(n));
	return x + n;
}

static inline wnat
wnat_sub(wnat x, wnat n)
{
	assert(IS_WNAT(x) && IS_WNAT(n));
	assert(wnat_leq(n, x));
	return x - n;
}

#endif	/* !_KMT_WNAT_H */
