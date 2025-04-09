#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd, newsock;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);
    char buffer[BUFFER_SIZE] = {0};
    char filename[BUFFER_SIZE] = {0};

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    listen(sockfd, 5);
    printf("Waiting for connection...\n");

    newsock = accept(sockfd, (struct sockaddr *)&client, &len);
    if (newsock < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    if (recv(newsock, filename, sizeof(filename), 0) < 0) {
        perror("Error receiving filename");
        close(newsock);
        close(sockfd);
        return 1;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        char *error_msg = "File not found";
        send(newsock, error_msg, strlen(error_msg), 0);
        perror("File not found");
    } else {
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            send(newsock, buffer, strlen(buffer), 0);
            memset(buffer, 0, sizeof(buffer));
        }
        printf("File sent to client.\n");
        fclose(file);
    }

    close(newsock);
    close(sockfd);
    return 0;
}

