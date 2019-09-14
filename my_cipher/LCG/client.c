#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

static unsigned int seed,a = 214013,b = 2531011,m = 1 << 31;
static unsigned char stream_block[4];

static void encrypt(char*);

int main(int argc,char **argv){
	int sock,i;
	ssize_t data_size;
	char message_recv[1024],message_send[1024];
	struct sockaddr_in server;

	if(argc != 4){
		fprintf(stderr,"usage: ./main <ip-addr> <port-num> <seed>\n");
		exit(1);
	}

	seed = atoi(argv[3]);
	memcpy(stream_block,&seed,4);

	server.sin_addr.s_addr = inet_addr(argv[1]);
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[2]));

	sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(sock == -1){
		perror("socket");
		exit(1);
	}
	printf("socket created\n");

	if(connect(sock,(struct sockaddr*)&server,sizeof(server)) < 0){
		perror("connect");
		exit(1);
	}
	printf("connected\n");

	printf("Client : ");
	scanf("%s",message_send);
	for(i = 0;i < strlen(message_send);i++){
		encrypt(&message_send[i]);
	}
	while(send(sock,message_send,strlen(message_send),0) > 0){
		printf("Client : ");
		scanf("%s",message_send);
		for(i = 0;i < strlen(message_send);i++){
			encrypt(&message_send[i]);
		}
	}
}

static void encrypt(char *data){
	static int iter = 0;

	char d = *data;
	*data ^= stream_block[iter];
	printf("%c x %d => %c\n",d,*(unsigned int*)stream_block,*data);
	
	iter = (iter + 1) % 4;
	if(iter == 0){
		unsigned int *ptr = (unsigned int*)stream_block;
		*ptr = (a * (*ptr) + b) % m;
	}
}
