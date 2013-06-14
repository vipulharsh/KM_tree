#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>

#include "petrinet.h"
#include "tree.h"
#include "covtree.h"

int main(int argc, char *argv[])
{
	FILE *fp;
	net *PetriNet;
	node *root;

	if (argc != 2) {
		errx(EXIT_FAILURE, "wrong number of arguments");
		/* NOTREACHED */
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		err(EXIT_FAILURE, "Unable to open `%s' for read", argv[1]);
		/* NOTREACHED */
	}
	petrinet_read(fp, &PetriNet);
	fclose(fp);

	//printf("Number of transitions : %d \n" , (PetriNet)->trans_count);

	fp = fopen("res.txt", "w");
	if (fp == NULL) {
		err(EXIT_FAILURE, "Unable to open `%s' for write", "res.txt");
		/* NOTREACHED */
	}
	petrinet_write(fp, PetriNet);

	//node_root(PetriNet);
	root = covtree_original_km(PetriNet);
	node_write(fp, root);
	fclose(fp);

	return 0;
}
