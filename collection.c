#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "collection.h"

typedef struct item {
	void		*data;		/* opaque user data */
	struct item	*next;
} item;

/*
 * XXX	Maintain a global pool of free items.
 */

typedef struct {
	item		*first;
} list;

typedef struct {
	item		*first;
	item		**last;
} queue;

static void		*list_create(void);
static void		 list_put(void *, void *);
static void		*list_get(void *);
static int		 list_empty(void *);

static void		*queue_create(void);
static void		 queue_put(void *, void *);
static void		*queue_get(void *);
static int		 queue_empty(void *);

const colmgr list_manager = {
	.create = list_create,
	.put = list_put,
	.get = list_get,
	.empty = list_empty,
};

const colmgr queue_manager = {
	.create = queue_create,
	.put = queue_put,
	.get = queue_get,
	.empty = queue_empty,
};

static void *
list_create(void)
{
	list *l;

	l = malloc(sizeof(*l));
	l->first = NULL;
	return l;
}

static void
list_put(void *x, void *d)
{
	list *l = (list *)x;
	item *n;

	assert(l != NULL);
	n = malloc(sizeof(*n));
	n->data = d;
	n->next = l->first;
	l->first = n;
}

static void *
list_get(void *x)
{
	list *l = (list *)x;
	item *n;
	void *ret;

	assert(l != NULL);
	assert(l->first != NULL);
	n = l->first;
	l->first = n->next;
	ret = n->data;
	free(n);
	return ret;
}

static int
list_empty(void *x)
{
	list *l = (list *)x;

	assert(l != NULL);
	return (l->first == NULL);
}

static void *
queue_create(void)
{
	queue *q;

	q = malloc(sizeof(*q));
	q->first = NULL;
	q->last = &q->first;
	return q;
}

static void
queue_put(void *x, void *d)
{
	queue *q = (queue *)x;
	item *n;

	assert(q != NULL);
	n = malloc(sizeof(*n));
	n->data = d;
	n->next = NULL;
	*q->last = n;
	q->last = &n->next;
}

static void *
queue_get(void *x)
{
	queue *q = (queue *)x;
	item *n;
	void *ret;

	assert(q != NULL);
	assert(q->first != NULL);
	n = q->first;
	q->first = n->next;
	if (q->first == NULL)
		q->last = &q->first;
	ret = n->data;
	free(n);
	return ret;
}

static int
queue_empty(void *x)
{
	queue *q = (queue *)x;

	assert(q != NULL);
	return (q->first == NULL);
}
