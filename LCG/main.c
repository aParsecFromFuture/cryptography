#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define A 213013
#define B 2531011

struct lcg32{
	uint32_t m;
	uint32_t a;
	uint32_t b;
	uint32_t state;
	uint8_t order;
};

void lcg32_init(struct lcg32*,uint32_t,uint32_t,uint32_t);
void lcg32_set_seed(struct lcg32*,uint32_t); 
uint32_t lcg32_next(struct lcg32*);
uint32_t lcg32_enc(struct lcg32*,void*,size_t);
void lcg32_info(const struct lcg32*);

int main(int argc,char **argv){
	struct lcg32 lcg;
	uint8_t buffer[128];
	ssize_t data_size;
	FILE *inp,*out;
	if(argc != 4){
		fprintf(stderr,"usage : ./main <seed> <inp-file> <out-file>\n");
		exit(1);
	}

	lcg32_init(&lcg,A,B,1 << 31);
	lcg32_set_seed(&lcg,atoi(argv[1]));

	inp = fopen(argv[2],"r");
	out = fopen(argv[3],"w");

	if(!inp || !out){
		perror("fopen");
		exit(1);
	}

	while((data_size = fread(buffer,1,sizeof(buffer),inp)) > 0){
		lcg32_enc(&lcg,buffer,data_size);
		fwrite(buffer,1,data_size,out);
	}

	fclose(inp);
	fclose(out);
}

void lcg32_init(struct lcg32 *lcg,uint32_t a,uint32_t b,uint32_t m){
	if(lcg){
		lcg->m = m;
		lcg->a = a;
		lcg->b = b;
		lcg->order = 0;
	}
}

void lcg32_set_seed(struct lcg32 *lcg,uint32_t seed){
	lcg->state = seed;
	lcg->order = 0;
}

uint32_t lcg32_next(struct lcg32 *lcg){
	uint32_t output = lcg->state;
	lcg->state = (lcg->a * lcg->state + lcg->b) % lcg->m;
	return output;
}

uint32_t lcg32_enc(struct lcg32 *lcg,void *data,size_t data_len){
	uint8_t *ptr,*data_iter;
	int i;
	data_iter = data;
	for(i = 0;i < data_len;i++){
		ptr = ((uint8_t*)&lcg->state) + lcg->order;
		data_iter[i] ^= *ptr;
		lcg->order = (lcg->order + 1) % 4;
		if(lcg->order == 0){
			lcg32_next(lcg);
		}
	}

}

void lcg32_info(const struct lcg32 *lcg){
	printf("*** Linear Conguential Generator ***\n");
	printf("m : %u\n",lcg->m);
	printf("a : %u\n",lcg->a);
	printf("b : %u\n",lcg->b);
	printf("state : %u\n\n",lcg->state);
}
