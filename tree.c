#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "marking.h"
#include "tree.h"

node *
node_create(void)
{
	assert(dimension > 0);
	return malloc(sizeof(node) + dimension * sizeof(wnat));
}

void
node_destroy(node *x)
{
	free(x);
}

node *
node_root(const net *pn)
{
	node *ret;

	ret = node_create();
	(void)memset(ret, 0, sizeof(node));
	marking_copy(ret->marking, pn->init);
	return ret;
}
