/*
 * Compile with: gcc -std=c99 -Wall -o coltest collection.c collection_test.c
 */

#include <stdio.h>
#include "collection.h"

static void
test_colmgr(const colmgr *colmgr)
{
	void *col;

	col = colmgr->create();
	printf("Is empty: %d\n", colmgr->empty(col));
	printf("Put(first)\n");
	colmgr->put(col, (void *)"first");
	printf("Put(second)\n");
	colmgr->put(col, (void *)"second");
	printf("Put(third)\n");
	colmgr->put(col, (void *)"third");
	printf("Is empty: %d\n", colmgr->empty(col));
	printf("Get: %s\n", (char *)colmgr->get(col));
	printf("Get: %s\n", (char *)colmgr->get(col));
	printf("Put(fourth)\n");
	colmgr->put(col, (void *)"fourth");
	printf("Is empty: %d\n", colmgr->empty(col));
	printf("Get: %s\n", (char *)colmgr->get(col));
	printf("Get: %s\n", (char *)colmgr->get(col));
	printf("Is empty: %d\n", colmgr->empty(col));
}

int main(int argc, char *argv[])
{
	printf("Testing with list...\n");
	test_colmgr(&list_manager);
	printf("\n");

	printf("Testing with queue...\n");
	test_colmgr(&queue_manager);
	printf("\n");

	return 0;
}
