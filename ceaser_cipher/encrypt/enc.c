#include <stdio.h>
#include <stdlib.h>

int mod(int,int);

int main(int argc,char **argv){
	FILE *inp,*out;
	int shift;
	char ch;
	if(argc != 4){
		fprintf(stderr,"Usage : ./main <input-file> <output-file> <shift-count>\n");
		exit(1);
	}

	inp = fopen(argv[1],"r");
	out = fopen(argv[2],"w");
	shift = atoi(argv[3]);

	if(!inp || !out){
		perror("fopen");
		exit(1);
	}

	ch = fgetc(inp);
	while(ch != EOF){
		if('a' <= ch && ch <= 'z'){
			ch = mod(ch - 'a' + shift,26) + 'a';
		}else if('A' <= ch && ch <= 'Z'){
			ch = mod(ch - 'A' + shift,26) + 'A';
		}
		fputc(ch,out);
		ch = fgetc(inp);
	}

	fclose(inp);
	fclose(out);
}

int mod(int num,int base){
	while(num < 0){
		num += base;
	}
	return num % base;
}
