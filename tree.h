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
 *
 *	The cover relation is maintained through the field cover stored in
 *	each node.  This field, when not NULL, points to another node that
 *	satisfies, in pseudo-code notation:
 *
 *	n.marking <= n.cover.marking
 *
 *	This implementation only permits functional cover relations: a node
 *	cannot have multiple coverers.
 */
typedef struct node {
	int		 processed;
	int id;
	struct node	*parent;
	transition	*action;
	struct node	*next;		/* pointer to the next sibling */
	struct node	*child;
	struct node	*cover;		/* node covering this one (if any) */
	wnat		marking[0];	/* variable length */
	/* DO NOT ADD ANYTHING HERE */
} node;

/*
 * node_create:
 *
 *	Allocates a new node.  The allocated memory is not initialized.
 *	Returns NULL on error.  See malloc(3).
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

/*
 * node_write:
 *
 *	Outputs, in text, the given node and its subtree.
 */
int		 node_write(FILE *stream, const node *);

#endif	/* !_KMT_TREE_H */
