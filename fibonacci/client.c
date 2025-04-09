#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd, n, count;
    struct sockaddr_in server;
    int fib[1024];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr *)&server, sizeof(server));

    // Input number
    printf("Enter a number to generate Fibonacci series up to: ");
    scanf("%d", &n);

    // Send the number to the server
    send(sockfd, &n, sizeof(int), 0);

    // Receive count and the Fibonacci series
    read(sockfd, &count, sizeof(int));
    read(sockfd, fib, sizeof(int) * count);

    // Print the series
    printf("Fibonacci series up to %d:\n", n);
    for (int i = 0; i < count; i++) {
        printf("%d ", fib[i]);
    }
    printf("\n");

    close(sockfd);
    return 0;
}

