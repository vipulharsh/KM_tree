#include "petrinet.h"

int main(int argc, char *argv[])
{
	FILE *fp;
	
	printf("flag 1");
	
	fp = fopen("ex2.in","r+");
	assert(fp!=NULL);
	
	printf("flag 2\n");
	
	
	net *PetriNet;
	petrinet_read(&PetriNet , fp);
	
	
	
	printf("here too - number of transitions : %d \n" , (PetriNet)->trans_count);
	

	
	FILE *fp1;
	
	fp1 = fopen("res.txt","w");
	
	assert(fp1!=NULL);
	petrinet_write(PetriNet , fp1);
	
	
	
	
	return 0;
}
