#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>

#include "petrinet.h"
#include "tree.h"
#include "covtree.h"
#include "collection.h"



void createDotFile(FILE *dotFile , node *root){
	
	
	if (dotFile!=NULL)
	{
		
		fprintf(dotFile, "digraph G { \n");
		
		void* unprocessedNodes = list_manager.create();
		list_manager.put(unprocessedNodes , root);
		fprintf(dotFile , " \"%p\"   [label = \"" , root); 
		marking_write(dotFile,root->marking);
		fprintf(dotFile , "\"]; \n");
	
		while(!list_manager.empty(unprocessedNodes))
		{
	  
		 node* temp = list_manager.get(unprocessedNodes);
		 node* child = temp->child; 
		 
			while(child!=NULL){
			    
			    list_manager.put(unprocessedNodes,child);
			    
			    fprintf(dotFile , "\"%p\"  [label = \"" , child); 
			    marking_write(dotFile,child->marking);
			    fprintf(dotFile , "\"]; \n");
			    fprintf(dotFile , "\"%p\" -> \"%p\" [color=\"red\" label=\"%s\"]\n" , temp , child ,child->action->name);
			    
			    if(child->cover!=NULL){
				fprintf(dotFile , "\"%p\" -> \"%p\" [color=\"green\" style=\"dashed\"]\n" , child , child->cover);
				}
				
				child = child->next;
				}
	    
	    }
	    
		fprintf(dotFile ,"}");
	    fclose(dotFile);
	    list_manager.destroy(unprocessedNodes);
   }
	else printf("Unable to open file");
	
}








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
	petrinet_read1(fp, &PetriNet);
	fclose(fp);

	//printf("Number of transitions : %d \n" , (PetriNet)->trans_count);

	fp = fopen("results/res.txt", "w");
	if (fp == NULL) {
		err(EXIT_FAILURE, "Unable to open `%s' for write", "res.txt");
		/* NOTREACHED */
	}
	
	
	petrinet_write(fp, PetriNet);
	
	root = covtree_original_km(PetriNet, &list_manager);

	
	node_write(fp, root);
	 FILE *dotFile1;
	dotFile1= fopen("results/tree.dot","w");
	createDotFile(dotFile1,root);


	
	
	fprintf(fp," ---- cov -reduced ----- \n");
	
	node *root1 = covtree_reduced_km(PetriNet, &list_manager);
	node_write(fp,root1);

		fprintf(fp," ---- finkel mct ----- \n");
   
	FILE *dotFile2;
	dotFile2= fopen("results/tree1.dot","w");
	createDotFile(dotFile2,root1);


	node *root2 = covtree_finkel_mct(PetriNet, &list_manager);
	node_write(fp,root2);
	fclose(fp);
	FILE *dotFile3;
	dotFile3= fopen("results/tree2.dot","w");
	createDotFile(dotFile3,root2);







	int result = covtree_complete(PetriNet , root);
	
	printf("The result is %d \n", result);
//	printf("root - covered %d \n" , covtree_covers(((root->child)->next)->marking , root->child));
    



	return 0;
}
