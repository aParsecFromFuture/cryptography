#include <stdio.h>
#include <stdlib.h>

int gcd(int,int);
int mod(int,int);

int main(int argc,char **argv){
	FILE *inp,*out;
	int key_a,key_b;
	char ch;
	if(argc != 5){
		fprintf(stderr,"Usage : ./enc <input-file> <output-file> <key-a> <key-b>\n");
		exit(1);
	}

	inp = fopen(argv[1],"r");
	out = fopen(argv[2],"w");
	key_a = atoi(argv[3]);
	key_b = atoi(argv[4]);

	if(gcd(key_a,26) != 1){
		fprintf(stderr,"Error : key-a value is not a coprime to alphabet-length(26)\n");
		exit(1);
	}

	if(!inp || !out){
		perror("fopen");
		exit(1);
	}

	ch = fgetc(inp);
	while(ch != EOF){
		if('a' <= ch && ch <= 'z'){
			ch = mod(key_a * (ch - 'a') + key_b,26) + 'a';
		}else if('A' <= ch && ch <= 'Z'){
			ch = mod(key_a * (ch - 'A') + key_b,26) + 'A';
		}
		fputc(ch,out);
		ch = fgetc(inp);
	}

	fclose(inp);
	fclose(out);
}

int gcd(int num_1,int num_2){
	int gcd,iter_count,i;

	iter_count = (num_1 < num_2)? num_1 : num_2;
	gcd = 1;
	for(i = 2;i <= iter_count;i++){
		if(num_1 % i == 0 && num_2 % i == 0){
			gcd = i;
		}
	}
	return gcd;
}

int mod(int num,int base){
	while(num < 0){
		num += base;
	}
	return num % base;
}
