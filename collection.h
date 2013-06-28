#ifndef _KMT_COLLECTION_H
#define _KMT_COLLECTION_H

typedef struct {
	void		*(*create)(void);
	void		 (*destroy)(void *);
	void		 (*put)(void *, const void *);
	void		*(*get)(void *);
	int		 (*empty)(void *);
} colmgr;

extern const colmgr list_manager;
extern const colmgr queue_manager;

#endif	/* !_KMT_COLLECTION_H */
