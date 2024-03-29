#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//server
int  server(int port)
{

  int sockfd;
  struct sockaddr_in si_me, si_other;
  char buffer[1024];
  socklen_t addr_size;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  memset(&si_me, '\0', sizeof(si_me));
  si_me.sin_family = AF_INET;
  si_me.sin_port = htons(port);
  si_me.sin_addr.s_addr = inet_addr("127.0.0.1");

  bind(sockfd, (struct sockaddr*)&si_me, sizeof(si_me));
  addr_size = sizeof(si_other);
  recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)& si_other, &addr_size);
  printf("[+]Data Received: %s", buffer);

  return 0;
}

//client
int client(int port)
{

  int sockfd;
  struct sockaddr_in serverAddr;
  char buffer[1024];
  socklen_t addr_size;

  sockfd = socket(PF_INET, SOCK_DGRAM, 0);
  memset(&serverAddr, '\0', sizeof(serverAddr));

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(port);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  strcpy(buffer, "Hello Server\n");
  sendto(sockfd, buffer, 1024, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
  printf("[+]Data Send: %s", buffer);

}


void usage(char *prog) {
  	printf("Usage: \n");
	printf("     ./%s rc \n", prog);
	printf("               or \n");
	printf("     ./%s ep \n", prog);

}

int rc_ep_sample(int mode)
{	
	int ret = 0;
	if(mode == 0) {
		ret = server(8080);
	} else if(mode == 1) {
		ret = client(8080);
	
	} else {
		printf("wrong mode \n");
	}

	return 0;
}
int main(int argc, char *argv[]) 
{ 
	int ret = 0;

	if (argc == 1) {
	    usage(argv[0]);
	    exit(0);
	}

	if(strcmp("rc",  argv[1]) == 0) {
		ret = rc_ep_sample(0);
		if(ret != 0)
		{
			printf("Error: %d \n", ret);
			return 0;
		}
	} else if (strcmp("ep",  argv[1]) == 0) {
		ret = rc_ep_sample(1); 
		if(ret != 0)
		{
			printf("Error: %d \n", ret);
			return 0;
		}
	} else {
		usage(argv[0]);
	}
	

	return 0;
}
