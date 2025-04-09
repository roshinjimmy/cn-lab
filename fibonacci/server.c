#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd, newsock, n;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);
    int fib[1024];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    bind(sockfd, (struct sockaddr *)&server, sizeof(server));
    listen(sockfd, 5);

    printf("Server: Listening on port 8080...\n");

    newsock = accept(sockfd, (struct sockaddr *)&client, &len);
    read(newsock, &n, sizeof(int));

    // Generate Fibonacci series up to n
    fib[0] = 0;
    fib[1] = 1;
    int i = 2, count = 2;
    while (1) {
        fib[i] = fib[i - 1] + fib[i - 2];
        if (fib[i] > n) break;
        i++;
        count++;
    }

    // Send count and the series
    send(newsock, &count, sizeof(int), 0);
    send(newsock, fib, sizeof(int) * count, 0);

    close(newsock);
    close(sockfd);
    return 0;
}

