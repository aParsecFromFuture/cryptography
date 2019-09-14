#include <stdio.h>
#include <stdlib.h>

int main(int argc,char **argv){
	FILE *inp,*out;
	int key_length,data_size,i;
	char *key,*buffer,ch;
	if(argc != 5){
		fprintf(stderr,"usage : ./main <src-file> <dst-file> <key> <key-len>\n");
		exit(1);
	}

	inp = fopen(argv[1],"r");
	out = fopen(argv[2],"w");

	if(!inp || !out){
		perror("fopen");
		exit(1);
	}

	key_length = atoi(argv[4]);
	if(key_length % 8 != 0){
		fprintf(stderr,"key length should be divisible to 8");
		exit(1);
	}

	key_length /= 8;

	key = malloc(sizeof(char) * key_length);
	for(i = 0;i < key_length;i++){
		key[i] = argv[3][i];
	}
	buffer = malloc(sizeof(char) * key_length);

	while((data_size = fread(buffer,1,key_length,inp)) > 0){
		for(i = 0;i < key_length;i++){
			buffer[i] ^= key[i];
		}
		fwrite(buffer,1,key_length,out);
	}

	fclose(inp);
	fclose(out);
}
