#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include "collection.h"

typedef struct{
	int place;
	char val[100];
} pair;



int index(char *pch , void *places_list){
	
	int index=0;
	
	void *temp = list_manager.create();
	while(!list_manager.empty(places_list)){
		char* m = list_manager.get(places_list);
		list_manager.put(temp , m);
		if(strcmp(m , pch) == 0){
			while(!list_manager.empty(temp)){
		     list_manager.put(places_list , list_manager.get(temp));
		  }
		  return index;
		}
		else index++; 
	}
   while(!list_manager.empty(temp)){
		     list_manager.put(places_list , list_manager.get(temp));
		  }
	return -1;
	
}






int notPresent(char *pch , void *places_list){
	
	void *temp = list_manager.create();
	while(!list_manager.empty(places_list)){
	    char* m = list_manager.get(places_list);
		list_manager.put(temp , m);
		if(strcmp(m , pch) == 0){
		  while(!list_manager.empty(temp)){
		     list_manager.put(places_list , list_manager.get(temp));
		  }
		  return 0;
	    }
	 }


   while(!list_manager.empty(temp)){
		     list_manager.put(places_list , list_manager.get(temp));
		  }
   return 1;		  
}





int main(int argc, char *argv[])
{
	FILE *fp;
	fp = fopen(argv[1], "r");
	
	char curr_char;
	
	char last_char='%';
	
	int flag=0; //to remove the initial garbage
	int trans_count=0;
	
	char transitions[100][3][80]; //to store transitions
	
	
	
	
	while((curr_char=fgetc(fp))!= EOF){
		
		if(flag==0 && curr_char!='t') continue;  //not seen the first transition
		
		if(flag==0 && curr_char== 't'){        
			last_char= curr_char;
			curr_char = fgetc(fp);
			if(curr_char == EOF){
				err(EXIT_FAILURE, "Something wrong");
				break;
			}
			if(curr_char=='r') {
				flag=1;
				last_char='|';
				printf("|");
				trans_count++;
				continue;
			}
			else{
			last_char='%';
			continue;
		    }
		}
	//removed the first redundant line	
		
	
		if(curr_char=='t'){
		 last_char= curr_char;
			curr_char = fgetc(fp);
			if(curr_char == EOF){
				err(EXIT_FAILURE, "Something wrong");
				break;
			}
			if(curr_char=='r') {
				last_char='|';
				printf("|");
				trans_count++;
				continue;
			}
		}
		
		
		
		if(last_char=='|'){
			last_char = curr_char;
			 while(last_char==' ' || last_char=='\t' || last_char=='\n'){
				curr_char = fgetc(fp);
				last_char = curr_char;
		     }
		    
		    int t=0;
		    while(!(last_char==' ' || last_char=='\t' || last_char=='\n')){
			 transitions[trans_count-1][0][t] = last_char;
			 t++;
			 last_char =  (curr_char = fgetc(fp));
			 }
		    transitions[trans_count-1][0][t] = '\0';  
		    
		    
		    
	//	    printf("trans_name : %s \n" , transitions[trans_count-1][0]);
		    
		    
		    while(last_char==' ' || last_char=='\t' || last_char=='\n'){
			 last_char =  (curr_char = fgetc(fp));
			 }
		    
		    if(last_char=='['){
				last_char =  (curr_char = fgetc(fp));
				while(!(last_char=='[' || last_char== ']'))
				  last_char =  (curr_char = fgetc(fp));
		    }
		    
		    
		    last_char =  (curr_char = fgetc(fp));
		    while(last_char==' ' || last_char=='\t' || last_char=='\n'){
			 last_char =  (curr_char = fgetc(fp));
		    }
		    
		    
		    t=0;
		    while(!(last_char=='-')){
			 transitions[trans_count-1][1][t] = last_char;
			 t++;
			 last_char =  (curr_char = fgetc(fp));
			 }
		    transitions[trans_count-1][1][t] = '\0';  
		//    printf("trans_input: %s \n" ,transitions[trans_count-1][1]);

		    
		    while(last_char=='-' || last_char==' ' || last_char=='>' || last_char=='\t')
		      last_char =  (curr_char = fgetc(fp));
		    
		    
		    t=0; 
		    while(last_char!='\n'){
				transitions[trans_count-1][2][t] = last_char;
				t++;
				last_char =  (curr_char = fgetc(fp));
			}
			transitions[trans_count-1][2][t] = '\0';
		//	printf("trans_output: %s \n" , transitions[trans_count-1][2]);
				
		    continue;
		}
		
		if(last_char=='\n' && curr_char == 'p'){
		 last_char =  (curr_char = fgetc(fp));
		 while(last_char!='\n' || last_char!=EOF){
			 last_char =  (curr_char = fgetc(fp));
			 if(last_char == EOF) break;
			 printf("%c ",last_char);
		    }
		  continue;    
		}		
		
	}
	
	int h;
	
	void *places_list = list_manager.create();
	
	int place_count = 0;
	

	char * so;
	for(h=0; h<trans_count; h++){
		 
//		 printf ("Splitting input string \"%s\" into tokens:\n",transitions[h][1]);
		 so = strtok (transitions[h][1]," ");
		 
		 while (so != NULL)
			{
		
			int span = strcspn(so , "*");
			char *pch =  malloc(span+1);
			strncpy(pch , so , span);
		 	printf ("%s\n",pch);
			if(notPresent(pch , places_list)){
				char *placeName = malloc(strlen(pch) + 1);
				strcpy(placeName , pch);
				list_manager.put(places_list , placeName);
				place_count++;
			}
			so = strtok (NULL, " ");
		  }
//		printf ("Splitting output string \"%s\" into tokens:\n",transitions[h][2]);
		 so = strtok (transitions[h][2]," ");
		 while (so != NULL)
			{
			int span = strcspn(so , "*");
			char *pch =  malloc(span+1);
			strncpy(pch , so , span);
		 	printf ("%s\n",pch);
			if(notPresent(pch , places_list)){
				char *placeName = malloc(strlen(pch) + 1);
				strcpy(placeName , pch);
				list_manager.put(places_list , placeName);
				place_count++;
			}
			so = strtok (NULL, " ");
		  }
	}
	
	
//assume now we have place_list , trans_count ,place_count	,transitions
	
	
	 while(!list_manager.empty(places_list)){
	    char* m = list_manager.get(places_list);
	    printf("%s ,  mahanta ka udhaaran hain ye \n" , m);
	}

		printf("No of Places ; %d",place_count);
		printf("No  of transitions ; %d" , trans_count);

	
return 0;
}
