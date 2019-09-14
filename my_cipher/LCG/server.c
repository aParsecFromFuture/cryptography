#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

static unsigned int seed,a = 214013,b = 2531011,m = 1 << 31;
static unsigned char stream_block[4];

static void encrypt(char*);

int main(int argc,char **argv){
	int sock,i,client_sock;
	ssize_t data_size;
	socklen_t sock_len;
	char message_send[1024],message_recv[1024];
	struct sockaddr_in server,client;

	if(argc != 3){
		fprintf(stderr,"usage : ./main <port-num> <seed>\n");
		exit(1);
	}

	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[1]));

	seed = atoi(argv[2]);
	memcpy(stream_block,&seed,4);

	sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(sock == -1){
		perror("socket");
		exit(1);
	}
	printf("socket created\n");

	if(bind(sock,(struct sockaddr*)&server,sizeof(server)) < 0){
		perror("bind");
		exit(1);
	}
	printf("bind done\n");

	sock_len = sizeof(struct sockaddr_in);

	listen(sock,1);
	printf("waiting for incoming connection...\n");

	client_sock = accept(sock,(struct sockaddr*)&client,(socklen_t*)&sock_len);
	if(client_sock == -1){
		perror("connect");
		exit(1);
	}
	printf("client connected\n");

	while((data_size = recv(client_sock,message_recv,sizeof(message_recv),0)) > 0){
		for(i = 0;i < data_size;i++){
			encrypt(&message_send[i]);
		}
		message_recv[data_size] = 0;
		
		printf("Client : %s\n",message_recv);
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
