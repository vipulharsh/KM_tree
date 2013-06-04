#ifndef _KMT_TREE_H
#define _KMT_TREE_H

#include "petrinet.h"

/*
 * node:
 *
 *	This structure defines the nodes of Karp&Miller trees.  The children
 *	of a node are stored by the fields child and next.  The former is
 *	the first child, and the latter is the next sibling.
 *
 *	Each node is labeled by a marking.  The array defining this marking
 *	is stored within the node itself.
 */
typedef struct node {
	struct node	*parent;
	transition	*action;
	struct node	*next;  //pointer to the next sibling
	struct node	*child;
	wnat		marking[0];	/* variable length */
} node;

/*
 * node_create:
 *
 *	Allocates a new node.  The contents of the node are unspecified.
 */
node		*node_create(void);

void		 node_destroy(node *);

/*
 * node_root:
 *
 *	Creates a root node.  The node's marking is equal to the initial
 *	marking of the Petri net.  All other fields are zeroed.
 */
node		*node_root(const net *);

/*
 * node_expand_all:
 *
 *	Creates all children of the given node.  The children are in one-to-
 *	one correspondance with the transitions that enabled from the given
 *	node's marking.  The marking of each child satisfies, in pseudo-code
 *	notation:
 *
 *	c.marking == c.parent.marking - c.action.input + c.action.output
 */
void		 node_expand_all(const net *, node *);

/*
 * node_expand_one:
 *
 *	Creates a child of the given node, and returns it.  This function
 *	returns NULL if the given transition is not enabled from the given
 *	node's marking.  The marking the child satisfies, in pseudo-code
 *	notation:
 *
 *	c.marking == c.parent.marking - c.action.input + c.action.output
 */
node		*node_expand_one(const transition *, node *);

/* node_write:
 *
 *	Outputs, in text, the given node and its subtree.
 */
int		 node_write(const node *, FILE *stream);

#endif	/* !_KMT_TREE_H */
