#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd, number;
    struct sockaddr_in server;
    char buffer[1024] = {0};

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr *)&server, sizeof(server));

    printf("Enter a number: ");
    scanf("%d", &number);

    send(sockfd, &number, sizeof(int), 0);

    read(sockfd, buffer, sizeof(buffer));
    printf("Server says: %s\n", buffer);

    close(sockfd);

    return 0;
}

