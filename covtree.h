#ifndef _KMT_COVTREE_H
#define _KMT_COVTREE_H

#include "tree.h"
#include "list_nodes.h"
/*
 * covtree_complete:
 *
 *	Checks that the given coverability tree is complete, i.e., that the
 *	downward closure of its set of nodes is an inductive invariant.
 */
int		 covtree_complete(const net *, const node *);

/*
 * covtree_covers
 * 
 * Checks that the given marking is covered by some node in the given 
 * coverability tree
 * 
 */ 
int		 covtree_covers(wnat*, const node *);

/*
 * covtree_original_km:
 *
 *	Computes the Karp&Miller tree, as defined in the seminal paper by
 *	Karp & Miller (1969).
 */
node		*covtree_original_km(const net *);

/*
 * covtree_reduced_km:
 *
 *	Computes a reduced Karp&Miller tree.  This tree is a prefix of the
 *	original Karp&Miller tree, and is obtained as follows.
 *  
 * A branch is not continued if its smaller than an ancestor
 *	
 */
node		*covtree_reduced_km(const net *);

/*
 * covtree_finkel_mct:
 *
 *	Computes the minimal coverability tree, as defined by Finkel (1990).
 *	Recall that this tree may be incomplete.  A counter-example has been
 *	given by Geeraerts et al. (2007).
 */
node		*covtree_finkel_mct(const net *);

/*
 * accel:
 *
 *	Accelerates a node with respect to its ancestors.
 *
 *	Note: doesn't need the Petri net as argument.
 */
int		 accel(node *);

/*
 * equal_ancestor:
 *
 *	Returns 1 if the given node has the same marking as one of its
 *	ancestors.  Returns 0 otherwise.
 */
int		 leq_ancestor(node *);

/*
 * leq_ancestor:
 *
 *	Returns 1 if the given node's marking is less than one of its
 *	ancestors.  Returns 0 otherwise.
 */
int		 equal_ancestor(node *);


#endif	/* !_KMT_COVTREE_H */
