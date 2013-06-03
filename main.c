#include "petrinet.h"

int main(int argc, char *argv[])
{
	FILE *fp;
	fp = fopen("ex2.in","r+");
	assert(fp!=NULL);
	
	net *PetriNet;
	petrinet_read(&PetriNet , fp);
	return 0;
}
