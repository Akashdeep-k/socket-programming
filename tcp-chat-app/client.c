#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(8080);

    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    char message[255];

    while (1)
    {
        printf("client: ");
        bzero(&message, sizeof(message));
        fgets(message, sizeof(message), stdin);
        send(sockfd, message, strlen(message), 0);

        bzero(&message, sizeof(message));
        recv(sockfd, message, sizeof(message), 0);
        printf("server: %s", message);
    }
    close(sockfd);
    return 0;
}