#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <inttypes.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

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

/*
 * getusertime:
 *
 *	Returns the total amount of time spent executing in user mode (see
 *	getrusage(2)).
 */
static int	 getusertime(struct timeval *);

/* The last component of the command line's program name. */
static const char *progname;


int
createDotFile(FILE *dotFile, node *root)
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
	return 0;
}








int main(int argc, char *argv[])
{
	struct timeval start, end, duration;
	node *(*engine)(const net *, const colmgr *);
	int (*parser)(FILE *, net **);
	const colmgr *wlmgr;
	char *dotfile, *txtfile;
	int quiet, validate;
	FILE *fp;
	net *PetriNet;
	node *root;
	char *suffix;
	int c;

	/* Program invocation name. */
	progname = strrchr(argv[0], '/');
	if (progname != NULL)
		progname++;
	else
		progname = argv[0];

	/* Default options. */
	engine = covtree_original_km;
	parser = NULL;
	wlmgr = &list_manager;
	dotfile = NULL;
	txtfile = NULL;
	quiet = 0;
	validate = 0;

	if (argc < 2) {
		warnx("Missing input file");
		usage();
		/* NOTREACHED */
	}

	/* Parse options. */
	while ((c = getopt(argc, argv, "cd:e:hqs:t:")) != -1) {
		switch (c) {
		case 'c':
			validate = 1;
			break;
		case 'd':
			dotfile = optarg;
			break;
		case 'e':
			if (strcmp(optarg, "km") == 0)
				engine = covtree_original_km;
			else if (strcmp(optarg, "km-red") == 0)
				engine = covtree_reduced_km;
			else if (strcmp(optarg, "mct") == 0)
				engine = covtree_finkel_mct;
			else {
				warnx("Invalid argument `%s' for -e", optarg);
				usage();
				/* NOTREACHED */
			}
			break;
		case 'q':
			quiet = 1;
			break;
		case 's':
			if (strcmp(optarg, "bfs") == 0)
				wlmgr = &queue_manager;
			else if (strcmp(optarg, "dfs") == 0)
				wlmgr = &list_manager;
			else {
				warnx("Invalid argument `%s' for -s", optarg);
				usage();
				/* NOTREACHED */
			}
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

	/* Expect only one remaining argument. */
	if (argc != 1) {
		warnx("Missing input file");
		usage();
		/* NOTREACHED */
	}

	/* Set up the parser according to the suffix of the input file. */
	suffix = rindex(argv[0], '.');
	if (suffix != NULL) {
		suffix++;
		if (strcasecmp(suffix, "in") == 0)
			parser = petrinet_read_in;
		else if (strcasecmp(suffix, "net") == 0)
			parser = petrinet_read_net;
		else {
			warnx("File name suffix `%s' unrecognized", suffix);
			usage();
			/* NOTREACHED */
		}
	} else {
		warnx("File name `%s' has no suffix", argv[0]);
		usage();
		/* NOTREACHED */
	}

	/* Nullify the pointers and streams that are released on failure. */
	fp = NULL;
	PetriNet = NULL;
	root = NULL;

	/* Open input file. */
	fp = fopen(argv[0], "r");
	if (fp == NULL) {
		warn("Unable to open `%s' for read", argv[0]);
		goto fail;
	}

	/* Read Petri net from input file. */
	if (parser(fp, &PetriNet) < 0) {
		warn("Unable to read Petri net from `%s'", argv[0]);
		goto fail;
	}
	(void)fclose(fp);
	fp = NULL;

	/* Write Petri net to the standard output. */
	printf("Input Petri Net: %u places, %u transitions\n",
	    PetriNet->place_count, PetriNet->trans_count);
	if (!quiet)
		(void)petrinet_write(stdout, PetriNet);

	/* Compute coverability tree. */
	if (getusertime(&start) != 0) {
		warn("Unable to get resource usage");
		goto fail;
	}
	root = engine(PetriNet, wlmgr);
	if (getusertime(&end) != 0) {
		warn("Unable to get resource usage");
		goto fail;
	}

	/* Display coverability tree computation time. */
	timersub(&end, &start, &duration);
	printf("Coverability tree: CPU user time: %jd.%06ld s\n",
	    (intmax_t)duration.tv_sec, (long int)duration.tv_usec);

	/* Validate coverability tree. */
	if (validate) {
		int result = covtree_complete(PetriNet, root);

		printf("Coverability tree: Completeness check: %s\n", result ? "ok" : "not ok");
//		printf("root - covered %d \n" , covtree_covers(((root->child)->next)->marking , root->child));
	}

	/* Write coverability tree to txt output file. */
	if (txtfile != NULL) {
		fp = fopen(txtfile, "w");
		if (fp == NULL) {
			warn("Unable to open `%s' for write", txtfile);
			goto fail;
		}
		if (node_write(fp, root) < 0) {
			warn("Unable to write txt coverability tree to `%s'",
			    txtfile);
			goto fail;
		}
		(void)fclose(fp);
		fp = NULL;
	}

	/* Write coverability tree to dot output file. */
	if (dotfile != NULL) {
		fp = fopen(dotfile, "w");
		if (fp == NULL) {
			warn("Unable to open `%s' for write", dotfile);
			goto fail;
		}
		if (createDotFile(fp, root) < 0) {
			warn("Unable to write dot coverability tree to `%s'",
			    dotfile);
			goto fail;
		}
		(void)fclose(fp);
		fp = NULL;
	}

	/* XXX Destroy the coverability tree */
	petrinet_destroy(PetriNet);
	exit(EXIT_SUCCESS);
	/* NOTREACHED */

fail:
	/* XXX Destroy the coverability tree */
	petrinet_destroy(PetriNet);
	if (fp != NULL)
		(void)fclose(fp);
	exit(EXIT_FAILURE);
	/* NOTREACHED */
}

static void
usage(void)
{
	fprintf(stderr,
	    "Usage: %s [options] <input file>\n"
	    "\n"
	    "  -c\t\tCheck completeness of coverability tree.\n"
	    "  -d <file>\tFile name of .dot output.\n"
	    "  -e {km, km-red, mct, mp}\n\t\tCoverability tree computation procedure.\n"
	    "  -s {bfs, dfs}\tOrder of exploration.\n"
	    "  -t <file>\tFile name of .txt output.\n"
	    "  -q\t\tQuiet output.\n"
	    "\n"
	    "The suffix of <input file> must be among {in, net}.\n",
	    progname);
	exit(EXIT_FAILURE);
	/* NOTREACHED */
}

static int
getusertime(struct timeval *tvp)
{
	struct rusage rusage;
	int res;

	if ((res = getrusage(RUSAGE_SELF, &rusage)) != 0) {
		return res;
	}
	*tvp = rusage.ru_utime;
	return res;
}
