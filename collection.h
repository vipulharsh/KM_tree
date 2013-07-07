#ifndef _KMT_COLLECTION_H
#define _KMT_COLLECTION_H

/*
 * colmgr:
 *
 *	This structure defines collection managers.  The fields are function
 *	pointers performing the following operations:
 *
 *		create()	return a new, empty collection
 *		destroy(c)	destroy the collection c
 *		put(c, e)	put element e into the collection c
 *		get(c)		get the next element from the collection c
 *		empty(c)	test whether the collection c is empty
 *
 *	The create function returns NULL on error (see malloc(3)).  The put
 *	function returns 0 on success, and -1 on error.
 */
typedef struct {
	void		*(*create)(void);
	void		 (*destroy)(void *);
	int		 (*put)(void *, const void *);
	void		*(*get)(void *);
	int		 (*empty)(void *);
} colmgr;

/* Collection manager with LIFO policy. */
extern const colmgr list_manager;

/* Collection manager with FIFO policy. */
extern const colmgr queue_manager;

#endif	/* !_KMT_COLLECTION_H */
