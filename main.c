#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <unistd.h>

#include "petrinet.h"
#include "tree.h"
#include "covtree.h"
#include "collection.h"

/*
 * usage:
 *
 *	Prints usage instructions and terminates the program.
 */
static void	 usage(void);

static const char *progname;


void createDotFile(FILE *dotFile , node *root)
{
	void *unprocessedNodes;

	assert(dotFile != NULL);

	fprintf(dotFile, "digraph G { \n");

	unprocessedNodes = list_manager.create();
	list_manager.put(unprocessedNodes , root);
	fprintf(dotFile , " \"%p\"   [label = \"" , root);
	marking_write(dotFile,root->marking);
	fprintf(dotFile , "\"]; \n");

	while (!list_manager.empty(unprocessedNodes)) {

		node* temp = list_manager.get(unprocessedNodes);
		node* child = temp->child;

		while (child!=NULL) {

			list_manager.put(unprocessedNodes,child);

			fprintf(dotFile , "\"%p\"  [label = \"" , child);
			marking_write(dotFile,child->marking);
			fprintf(dotFile , "\"]; \n");
			fprintf(dotFile , "\"%p\" -> \"%p\" [color=\"red\" label=\"%s\"]\n" , temp , child ,child->action->name);

			if (child->cover!=NULL) {
				fprintf(dotFile , "\"%p\" -> \"%p\" [color=\"green\" style=\"dashed\"]\n" , child , child->cover);
			}

			child = child->next;
		}

	}

	fprintf(dotFile ,"}");
	list_manager.destroy(unprocessedNodes);
}








int main(int argc, char *argv[])
{
	node *(*engine)(const net *, const colmgr *);
	const colmgr *wlmgr;
	char *dotfile, *txtfile;
	FILE *fp;
	net *PetriNet;
	node *root;
	int c;

	/* Program invocation name. */
	progname = strrchr(argv[0], '/');
	if (progname != NULL)
		progname++;
	else
		progname = argv[0];

	/* Default options. */
	engine = covtree_original_km;
	wlmgr = &list_manager;
	dotfile = NULL;
	txtfile = NULL;

	if (argc < 2) {
		usage();
		/* NOTREACHED */
	}

	while ((c = getopt(argc, argv, "e:s:d:t:")) != -1) {
		switch (c) {
		case 'e':
			if (strcmp(optarg, "km") == 0)
				engine = covtree_original_km;
			else if (strcmp(optarg, "km-red") == 0)
				engine = covtree_reduced_km;
			else if (strcmp(optarg, "mct") == 0)
				engine = covtree_finkel_mct;
			else
				usage();
			break;
		case 's':
			if (strcmp(optarg, "bfs") == 0)
				wlmgr = &queue_manager;
			else if (strcmp(optarg, "dfs") == 0)
				wlmgr = &list_manager;
			else
				usage();
			break;
		case 'd':
			dotfile = optarg;
			break;
		case 't':
			txtfile = optarg;
			break;
		case '?':
		default:
			usage();
			/* NOTREACHED */
		}
	}
	argc -= optind;
	argv += optind;

	if (argc != 1)
		usage();

	fp = fopen(argv[0], "r");
	if (fp == NULL) {
		err(EXIT_FAILURE, "Unable to open `%s' for read", argv[1]);
		/* NOTREACHED */
	}
	petrinet_read1(fp, &PetriNet);
	fclose(fp);

	//printf("Number of transitions : %d \n" , (PetriNet)->trans_count);

	if (txtfile != NULL) {
		fp = fopen(txtfile, "w");
		if (fp == NULL) {
			err(EXIT_FAILURE, "Unable to open `%s' for write", txtfile);
			/* NOTREACHED */
		}
		petrinet_write(fp, PetriNet);
	}

	root = engine(PetriNet, wlmgr);

	int result = covtree_complete(PetriNet , root);

	printf("The resulting tree is complete: %s\n", result ? "yes" : "no");
//	printf("root - covered %d \n" , covtree_covers(((root->child)->next)->marking , root->child));

	if (txtfile != NULL) {
		node_write(fp, root);
		fclose(fp);
	}

	if (dotfile != NULL) {
		fp = fopen(dotfile, "w");
		if (fp == NULL) {
			err(EXIT_FAILURE, "Unable to open `%s' for write", dotfile);
			/* NOTREACHED */
		}
		createDotFile(fp, root);
		fclose(fp);
	}

	return 0;
}

static void
usage(void)
{
	errx(EXIT_FAILURE,
	    "Usage: %s [options] <file>\n"
	    "  -e {km, km-red, mct, mp}\n\t\tCoverability tree computation procedure.\n"
	    "  -d <file>\tFile name of .dot output.\n"
	    "  -t <file>\tFile name of .txt output.\n"
	    "  -s {bfs, dfs}\tOrder of exploration.\n",
	    progname);
	/* NOTREACHED */
}
