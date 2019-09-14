#include <stdio.h>
#include <stdint.h>

struct lfsr32{
	uint32_t state;
	uint32_t key;
};

struct lfsr16{
	uint16_t state;
	uint16_t key;
};

struct lfsr8{
	uint8_t state;
	uint8_t key;
};

void lfsr32_init(struct lfsr32*,uint32_t,uint32_t);
int lfsr32_next(struct lfsr32*);
void lfsr32_info(const struct lfsr32*);
int lfsr32_check(struct lfsr32*);

void lfsr16_init(struct lfsr16*,uint16_t,uint16_t);
int lfsr16_next(struct lfsr16*);
void lfsr16_info(const struct lfsr16*);
int lfsr16_check(struct lfsr16*);

void lfsr8_init(struct lfsr8*,uint8_t,uint8_t);
int lfsr8_next(struct lfsr8*);
void lfsr8_info(const struct lfsr8*);
int lfsr8_check(struct lfsr8*);

int main(int argc,char **argv){
	struct lfsr16 lfsr;
	lfsr16_init(&lfsr,0x8013,10);
	printf("%d\n",lfsr16_check(&lfsr));
}

void lfsr32_init(struct lfsr32 *lfsr,uint32_t key,uint32_t state){
	lfsr->state = state;
	lfsr->key = key;
}

void lfsr16_init(struct lfsr16 *lfsr,uint16_t key,uint16_t state){
	lfsr->state = state;
	lfsr->key = key;
}

void lfsr8_init(struct lfsr8 *lfsr,uint8_t key,uint8_t state){
	lfsr->state = state;
	lfsr->key = key;
}

int lfsr32_next(struct lfsr32 *lfsr){
	int output,tmp = 0;
	output = lfsr->state & 0x1;

	tmp ^= ((lfsr->state & 0x00000001) & (lfsr->key & 0x00000001)) >> 0x00;
	tmp ^= ((lfsr->state & 0x00000002) & (lfsr->key & 0x00000002)) >> 0x01;
	tmp ^= ((lfsr->state & 0x00000004) & (lfsr->key & 0x00000004)) >> 0x02;
	tmp ^= ((lfsr->state & 0x00000008) & (lfsr->key & 0x00000008)) >> 0x03;
	
	tmp ^= ((lfsr->state & 0x00000010) & (lfsr->key & 0x00000010)) >> 0x04;
	tmp ^= ((lfsr->state & 0x00000020) & (lfsr->key & 0x00000020)) >> 0x05;
	tmp ^= ((lfsr->state & 0x00000040) & (lfsr->key & 0x00000040)) >> 0x06;
	tmp ^= ((lfsr->state & 0x00000080) & (lfsr->key & 0x00000080)) >> 0x07;
	
	tmp ^= ((lfsr->state & 0x00000100) & (lfsr->key & 0x00000100)) >> 0x08;
	tmp ^= ((lfsr->state & 0x00000200) & (lfsr->key & 0x00000200)) >> 0x09;
	tmp ^= ((lfsr->state & 0x00000400) & (lfsr->key & 0x00000400)) >> 0x0a;
	tmp ^= ((lfsr->state & 0x00000800) & (lfsr->key & 0x00000800)) >> 0x0b;
	
	tmp ^= ((lfsr->state & 0x00001000) & (lfsr->key & 0x00001000)) >> 0x0c;
	tmp ^= ((lfsr->state & 0x00002000) & (lfsr->key & 0x00002000)) >> 0x0d;
	tmp ^= ((lfsr->state & 0x00004000) & (lfsr->key & 0x00004000)) >> 0x0e;
	tmp ^= ((lfsr->state & 0x00008000) & (lfsr->key & 0x00008000)) >> 0x0f;
	
	tmp ^= ((lfsr->state & 0x00010000) & (lfsr->key & 0x00010000)) >> 0x10;
	tmp ^= ((lfsr->state & 0x00020000) & (lfsr->key & 0x00020000)) >> 0x11;
	tmp ^= ((lfsr->state & 0x00040000) & (lfsr->key & 0x00040000)) >> 0x12;
	tmp ^= ((lfsr->state & 0x00080000) & (lfsr->key & 0x00080000)) >> 0x13;
	
	tmp ^= ((lfsr->state & 0x00100000) & (lfsr->key & 0x00000000)) >> 0x14;
	tmp ^= ((lfsr->state & 0x00200000) & (lfsr->key & 0x00000000)) >> 0x15;
	tmp ^= ((lfsr->state & 0x00400000) & (lfsr->key & 0x00000000)) >> 0x16;
	tmp ^= ((lfsr->state & 0x00800000) & (lfsr->key & 0x00000000)) >> 0x17;
	
	tmp ^= ((lfsr->state & 0x01000000) & (lfsr->key & 0x01000000)) >> 0x18;
	tmp ^= ((lfsr->state & 0x02000000) & (lfsr->key & 0x02000000)) >> 0x19;
	tmp ^= ((lfsr->state & 0x04000000) & (lfsr->key & 0x04000000)) >> 0x1a;
	tmp ^= ((lfsr->state & 0x08000000) & (lfsr->key & 0x08000000)) >> 0x1b;

	tmp ^= ((lfsr->state & 0x10000000) & (lfsr->key & 0x10000000)) >> 0x1c;
	tmp ^= ((lfsr->state & 0x20000000) & (lfsr->key & 0x20000000)) >> 0x1d;
	tmp ^= ((lfsr->state & 0x40000000) & (lfsr->key & 0x40000000)) >> 0x1e;
	tmp ^= ((lfsr->state & 0x80000000) & (lfsr->key & 0x80000000)) >> 0x1f;

	lfsr->state >>= 1;
	lfsr->state |= (tmp << 0x1f);
	
	return output;
}

int lfsr16_next(struct lfsr16 *lfsr){
	int output,tmp = 0;
	output = lfsr->state & 0x1;

	tmp ^= ((lfsr->state & 0x0001) & (lfsr->key & 0x0001)) >> 0x00;
	tmp ^= ((lfsr->state & 0x0002) & (lfsr->key & 0x0002)) >> 0x01;
	tmp ^= ((lfsr->state & 0x0004) & (lfsr->key & 0x0004)) >> 0x02;
	tmp ^= ((lfsr->state & 0x0008) & (lfsr->key & 0x0008)) >> 0x03;
	
	tmp ^= ((lfsr->state & 0x0010) & (lfsr->key & 0x0010)) >> 0x04;
	tmp ^= ((lfsr->state & 0x0020) & (lfsr->key & 0x0020)) >> 0x05;
	tmp ^= ((lfsr->state & 0x0040) & (lfsr->key & 0x0040)) >> 0x06;
	tmp ^= ((lfsr->state & 0x0080) & (lfsr->key & 0x0080)) >> 0x07;
	
	tmp ^= ((lfsr->state & 0x0100) & (lfsr->key & 0x0100)) >> 0x08;
	tmp ^= ((lfsr->state & 0x0200) & (lfsr->key & 0x0200)) >> 0x09;
	tmp ^= ((lfsr->state & 0x0400) & (lfsr->key & 0x0400)) >> 0x0a;
	tmp ^= ((lfsr->state & 0x0800) & (lfsr->key & 0x0800)) >> 0x0b;
	
	tmp ^= ((lfsr->state & 0x1000) & (lfsr->key & 0x1000)) >> 0x0c;
	tmp ^= ((lfsr->state & 0x2000) & (lfsr->key & 0x2000)) >> 0x0d;
	tmp ^= ((lfsr->state & 0x4000) & (lfsr->key & 0x4000)) >> 0x0e;
	tmp ^= ((lfsr->state & 0x8000) & (lfsr->key & 0x8000)) >> 0x0f;
	
	lfsr->state >>= 1;
	lfsr->state |= (tmp << 0x0f);
	
	return output;
}

int lfsr8_next(struct lfsr8 *lfsr){
	int output,tmp = 0;
	output = lfsr->state & 0x1;

	tmp ^= ((lfsr->state & 0x01) & (lfsr->key & 0x01)) >> 0x00;
	tmp ^= ((lfsr->state & 0x02) & (lfsr->key & 0x02)) >> 0x01;
	tmp ^= ((lfsr->state & 0x04) & (lfsr->key & 0x04)) >> 0x02;
	tmp ^= ((lfsr->state & 0x08) & (lfsr->key & 0x08)) >> 0x03;
	
	tmp ^= ((lfsr->state & 0x10) & (lfsr->key & 0x10)) >> 0x04;
	tmp ^= ((lfsr->state & 0x20) & (lfsr->key & 0x20)) >> 0x05;
	tmp ^= ((lfsr->state & 0x40) & (lfsr->key & 0x40)) >> 0x06;
	tmp ^= ((lfsr->state & 0x80) & (lfsr->key & 0x80)) >> 0x07;

	lfsr->state >>= 1;
	lfsr->state |= (tmp << 0x07);
	
	return output;
}

void lfsr32_info(const struct lfsr32 *lfsr){
	printf("state : %08x\n",lfsr->state);
	printf("key : %08x\n",lfsr->key);
}

void lfsr16_info(const struct lfsr16 *lfsr){
	printf("state : %04x\n",lfsr->state);
	printf("key : %04x\n",lfsr->key);
}

void lfsr8_info(const struct lfsr8 *lfsr){
	printf("state : %02x\n",lfsr->state);
	printf("key : %02x\n",lfsr->key);
}

int lfsr32_check(struct lfsr32 *lfsr){
	int i,is_used[0xffffffff] = {0};
	for(i = 0;i < 0xffffffff;i++){
		lfsr32_next(lfsr);
		if(is_used[lfsr->state - 1]){
			return 1;
		}
		is_used[lfsr->state - 1] = 1;
	}
	return 0;
}

int lfsr16_check(struct lfsr16 *lfsr){
	int i,is_used[0xffff] = {0};
	for(i = 0;i < 0xffff;i++){
		lfsr16_next(lfsr);
		if(is_used[lfsr->state - 1]){
			return 1;
		}
		is_used[lfsr->state - 1] = 1;
	}
	return 0;
}

int lfsr8_check(struct lfsr8 *lfsr){
	int i,is_used[0xff] = {0};
	for(i = 0;i < 0xff;i++){
		lfsr8_next(lfsr);
		if(is_used[lfsr->state - 1]){
			return 1;
		}
		is_used[lfsr->state - 1] = 1;
	}
	return 0;
}

