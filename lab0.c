#define _GNU_SOURCE 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

struct Word{
	char* word;
	int count;
	struct Word* next;
};

#define ADD_PTR(p,x) ((char*)(p) + (x))
#define SUB_PTR(p,x) ((char*)(p) - (x))

int main(int argc, char** argv){
	int fflag = 0;
	int wflag = 0;
	char* dict_name;
	char* out_name;
	int getoptread;
	
	while((getoptread=getopt(argc,argv,"f:w:"))!=-1){
		switch(getoptread){
			case 'f':
				fflag = 1;
				dict_name = optarg;
				break;
			case 'w':
				wflag = 1;
				out_name = optarg;
				break;
		}
	}

	char* search_word = argv[optind];
	char* input = argv[optind+1];
    	FILE *input_file;
	size_t len = 0;
	ssize_t read;
	char* line = NULL;
	struct Word* root;
	struct Word* conductor;
	
	root = malloc(sizeof(struct Word));
	root->next = 0;
	root->word = "placeholderjusttocheckhaha";
    	if(fflag == 0){
		input_file = fopen(input, "r");
	}
	else{
		input_file = fopen(search_word, "r");
	}
	if(input_file==NULL){
		perror("Canot open input file\n");
        	exit(-1);
	}
	
	while((read = getline(&line, &len, input_file))!= -1){
		char* line_copy = strdup(line);
		char* p = strtok(line_copy," []$%_“”\"’—.,:;-!?/()*'@");
		while(p != NULL){
			conductor = root;
			while(strcmp(conductor->word,p)!=0&&conductor->next!=0){
				conductor = conductor->next;
				
			}
			if(strcmp(conductor->word,"placeholderjusttocheckhaha")==0){
				conductor->word = p;
				conductor->count = 1;
			}			
			else if(strcmp(conductor->word,p)==0){
				conductor->count = conductor->count+1;
			}	
			else{
				conductor->next = malloc(sizeof(struct Word));
				conductor = conductor->next;
				conductor->word = p;
				conductor->count = 1;	
				conductor->next = 0;
			}
			p = strtok(NULL," []$%_“”\"’—.,:;-!?/()*'@");
		}
	}
	conductor = root;
	if(fflag==0&&wflag==0){
		while(conductor->next!=0&&strcmp(conductor->word,search_word)!=0){
			conductor = conductor->next;
		}
			if(strcmp(conductor->word,search_word)==0){
                                printf(conductor->word);
                                printf(", ");
                                printf("%i",conductor->count);
                                printf("\n");
                        }
                        else{
                                printf("%s, not found\n", search_word);
                      	}
	}
	else if(fflag==0&&wflag!=0){
		while(conductor->next!=0&&strcmp(conductor->word,search_word)!=0){
                        conductor = conductor->next;
                }
		FILE *opf;
		opf = fopen(out_name, "w");
		if (opf == NULL) {
  			fprintf(stderr, "Can't open output file %s!\n",
          		out_name);
  			exit(1);
		}
		if(strcmp(conductor->word,search_word)==0){
			fprintf(opf, "%s, %i",conductor->word, conductor->count);
		}
		else{
			fprintf(opf, "%s, %i",search_word, 0);
		}
		fclose(opf);
	}
	else if(fflag!=0&&wflag==0){
		FILE *fp1;
		char oneword[100];
		char c;
		fp1 = fopen(dict_name,"r");
		while(c!=EOF){
			conductor = root;
			c = fscanf(fp1,"%s",oneword);
			char* point_word = oneword;
			while(conductor->next!=0&&strcmp(conductor->word,point_word)!=0){
                        	conductor = conductor->next;
                	}
                	if(strcmp(conductor->word,oneword)==0){
				printf(conductor->word);
                		printf(", ");
                		printf("%i",conductor->count);
                		printf("\n");
			}
			else{
				printf("%s, not found\n", point_word);
			}
		}
	}
	else{
		FILE *fp1;
                char oneword[100];
                char c;
                fp1 = fopen(dict_name,"r");
		FILE *opf;
                opf = fopen(out_name, "w");
                if (opf == NULL) {
                        fprintf(stderr, "Can't open output file %s!\n",
                        out_name);
                        exit(1);
                }
                while(c!=EOF){
			conductor = root;
                        c = fscanf(fp1,"%s",oneword);
                        while(conductor->next!=0&&strcmp(conductor->word,oneword)!=0){
                                conductor = conductor->next;
                        }
                	if(strcmp(conductor->word,oneword)==0){
                        	fprintf(opf, "%s, %i\n",conductor->word, conductor->count);
                	}
               		else{
                        	fprintf(opf, "%s, %i\n",oneword, 0);
                	}
		}
	}
	free(line);
     	fclose(input_file);
     	exit(EXIT_SUCCESS);
}
