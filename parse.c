#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>


int main(int argc, char *argv[])
{
	FILE *fp;
	fp = fopen(argv[1], "r");
	
	char curr_char;
	
	char last_char='%';
	
	int flag=0; //to remove the initial garbage
	int trans_count=0;
	
	
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
		
	
	
	
		
		
	//if last character was a bracket , then ignore
		if(last_char=='['){
			if(curr_char==']' || curr_char=='['){
				last_char = '%';  //brackets over
				continue;
			}
			else
			continue;
		}
		
		
		
		
		if(curr_char=='['){
			last_char= '[';
			continue;
		}
		
		
		
		
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
		    char trans_name[100];
		    int t=0;
		    while(!(last_char==' ' || last_char=='\t' || last_char=='\n')){
			 trans_name[t] = last_char;
			 t++;
			 curr_char = fgetc(fp);
			 last_char = curr_char;
		    }
		    trans_name[t] = '\0';  
		    
		    printf("trans_name : %s \n" , trans_name);
		    last_char  = '%';
		    continue;
		}
		
		
		
		
		
			
		
		 last_char=curr_char;
	     printf("%c",last_char);
				
		
	}
	
	printf("No of transitions ; %d",trans_count); 
	
	return 0;
}
