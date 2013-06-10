#include "petrinet.h"
#include "tree.h"
#include "covtree.h"
int main(int argc, char *argv[])
{
	FILE *fp;
	
	
	fp = fopen("ex2.in","r+");
	assert(fp!=NULL);
	
	
	
	net *PetriNet;
	petrinet_read(&PetriNet , fp);
	
	
	
	//printf("Number of transitions : %d \n" , (PetriNet)->trans_count);
	

	
	FILE *fp1;
	
	fp1 = fopen("res.txt","w");
	
	assert(fp1!=NULL);
	petrinet_write(PetriNet , fp1);
	
	
    //node_root(PetriNet);
	node *root1;
	root1 = covtree_original_km(PetriNet);
	
	node_write(root1 , fp1);
	
	fclose(fp1);
	return 0;
}
