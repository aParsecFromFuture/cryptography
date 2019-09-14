#include <stdio.h>
#include <stdlib.h>

int main(int argc,char **argv){
	FILE *inp,*out,*subs;
	int i,table_size = 0;
	char *subs_table_from,*subs_table_to,ch;
	if(argc != 4){
		fprintf(stderr,"Usage : ./enc <input-file> <output-file> <substitution-file>\n");
		exit(1);
	}

	inp = fopen(argv[1],"r");
	out = fopen(argv[2],"w");
	subs = fopen(argv[3],"r");

	if(!inp || !out || !subs){
		perror("fopen");
		exit(1);
	}

	ch = fgetc(subs);
	while(ch != EOF){
		if(ch == '\n'){
			table_size++;
		}
		ch = fgetc(subs);
	}
	fseek(subs,0,SEEK_SET);

	subs_table_from = malloc(sizeof(char) * table_size);
	subs_table_to = malloc(sizeof(char) * table_size);

	for(i = 0;i < table_size;i++){
		fscanf(subs,"%c %c\n",&subs_table_from[i],&subs_table_to[i]);
	}
	fclose(subs);

	ch = fgetc(inp);
	while(ch != EOF){
		for(i = 0;i < table_size;i++){
			if(ch == subs_table_from[i]){
				ch = subs_table_to[i];
			}
		}
		fputc(ch,out);
		ch = fgetc(inp);
	}

	fclose(inp);
	fclose(out);
}
