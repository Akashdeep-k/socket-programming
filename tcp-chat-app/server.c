#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr));
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(8080);
	
	bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	listen(sockfd, 5);
	
	int clientfd = accept(sockfd, NULL, NULL);
	char message[255];
	
	while(1){
		bzero(&message, sizeof(message));
		recv(clientfd, message, sizeof(message), 0);
		printf("client : %s", message);
		
		printf("server: ");
		bzero(&message, sizeof(message));
		fgets(message, sizeof(message), stdin);
		send(clientfd, message, strlen(message), 0);
	}
	close(clientfd);
	close(sockfd);
	return 0;
}
