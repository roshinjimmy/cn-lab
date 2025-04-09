#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd, n;
    struct sockaddr_in server;
    int buffer[1024][1024];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8080);

    connect(sockfd, (struct sockaddr *)&server, sizeof(server));

    // Input matrix size
    printf("Enter the size:\n");
    scanf("%d", &n);

    // Input matrix
    printf("Enter the matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &buffer[i][j]);
        }
    }

    // Send matrix size and data
    send(sockfd, &n, sizeof(int), 0);
    send(sockfd, buffer, sizeof(buffer), 0);

    close(sockfd);
    return 0;
}

