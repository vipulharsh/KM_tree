#ifndef _KMT_COVTREE_H
#define _KMT_COVTREE_H

#include "tree.h"
#include <stdlib.h>

/*
 * covtree_complete:
 *
 *	Checks that the given coverability tree is complete, i.e., that the
 *	downward closure of its set of nodes is an inductive invariant.
 */
int	covtree_complete(const net *, const node *);

/*
 * covtree_original_km:
 *
 *	Computes the Karp&Miller tree, as defined in the seminal paper by
 *	Karp & Miller (1969).
 */
node*  covtree_original_km(const net *);

/*
 * covtree_reduced_km:
 *
 *	Computes a reduced Karp&Miller tree.  This tree is a prefix of the
 *	original Karp&Miller tree, and is obtained as follows.
 *
 *	XXX Add the specification of the prefix.
 */
node*		covtree_reduced_km(const net *);

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
 * Accelerates a node with respect to its ancestors
 * NOTE :doesn't need the petri net as argument
 * 
 * 
 */
 
int accel(node *); 
 
 
 
 
 /*
  * equal_ancestor(x) : 
  * returns 1 if an ancestor's marking is same as that of x
  * 
  */ 
 
 int equal_ancestor(node *x);
 
 


/*
 * list_nodes:
 * A data structure to maintain a list of nodes 
 * Has one variable for a node pointer , and the other for the next item. 
 */ 
 
typedef struct list_nodes {
	struct list_nodes *next;
	node *x;
} list_nodes;
 
/*
 *The usual list operations 
 * 
 *pop_front : pops out the front element and returns the pointer to the node popped out 
 * 			  Note that it also modifies the list	
 *
 *push_front : pushes a given node to the front of the list   
 * 
 * 
 *empty : returns true if list is empty. returns false otherwise 
 */  

node* pop_front(list_nodes **x);


int push_front(list_nodes **list , node *n);

int empty(list_nodes *x);





#endif	/* !_KMT_COVTREE_H */
