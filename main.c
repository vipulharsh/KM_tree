#include "petrinet.h"
#include "tree.h"
int main(int argc, char *argv[])
{
	FILE *fp;
	
	//printf("flag 1");
	
	fp = fopen("ex2.in","r+");
	assert(fp!=NULL);
	
	//printf("flag 2\n");
	
	
	net *PetriNet;
	petrinet_read(&PetriNet , fp);
	
	
	
	//printf("here too - number of transitions : %d \n" , (PetriNet)->trans_count);
	

	
	FILE *fp1;
	
	fp1 = fopen("res.txt","w");
	
	assert(fp1!=NULL);
	petrinet_write(PetriNet , fp1);
	
	
    //node_root(PetriNet);
	node *root;
	covtree_original_km(PetriNet);
	
	
	printf("fl 1 \n");
	
	//node_expand_all(PetriNet , root);
	
	//node_expand_all(PetriNet ,root->child);
	
	
	//accel(root->child);
	
	
	
	//printf("testing %d \n", equal_ancestor(root->child->next));
	
	node_write(root , fp1);
	
	fclose(fp1);
	return 0;
}
