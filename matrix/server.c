#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd, newsock, n;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);
    int buffer[1024][1024];
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    bind(sockfd, (struct sockaddr *)&server, sizeof(server));
    listen(sockfd, 5);

    printf("Server: Server is listening at port 8080\n");

    newsock = accept(sockfd, (struct sockaddr *)&client, &len);

    // Read matrix size
    read(newsock, &n, sizeof(int));

    // Read matrix data
    read(newsock, buffer, sizeof(buffer));

    // Print received matrix
    printf("Received %dx%d Matrix:\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", buffer[i][j]);
        }
        printf("\n");
    }

    close(newsock);
    close(sockfd);

    return 0;
}

