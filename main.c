#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>

#include "petrinet.h"
#include "tree.h"
#include "covtree.h"
#include "worklist.h"

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

	fp = fopen("results/res.txt", "w");
	if (fp == NULL) {
		err(EXIT_FAILURE, "Unable to open `%s' for write", "res.txt");
		/* NOTREACHED */
	}
	
	
	petrinet_write(fp, PetriNet);
	
	root = covtree_original_km(PetriNet);
	node_write(fp, root);
	
	fprintf(fp," ---- cov -reduced ----- \n");
	
	node *root1 = covtree_reduced_km(PetriNet);
	node_write(fp,root1);
	fclose(fp);

	int result = covtree_complete(PetriNet , root);
	
	printf("The result is %d \n", result);
//	printf("root - covered %d \n" , covtree_covers(((root->child)->next)->marking , root->child));


	return 0;
}
