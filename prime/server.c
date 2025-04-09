#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>

bool is_prime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

int main() {
    int sockfd, newsock, number;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);
    char buffer[1024];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    bind(sockfd, (struct sockaddr *)&server, sizeof(server));
    listen(sockfd, 5);
    printf("Server: Waiting for connection...\n");

    newsock = accept(sockfd, (struct sockaddr *)&client, &len);
    read(newsock, &number, sizeof(int));
    printf("Server: Received number %d\n", number);

    if (is_prime(number)) {
        strcpy(buffer, "Prime");
    } else {
        strcpy(buffer, "Not Prime");
    }

    send(newsock, buffer, strlen(buffer), 0);
    close(newsock);
    close(sockfd);

    return 0;
}

