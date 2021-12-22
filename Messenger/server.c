#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080
#define END_STR "cya"

void closeConnection();

int main(int argc, char const *argv[]) {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char name[50] = {0};
    char otherName[50] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }

    printf("What is your name? ");
    fflush(stdout);
    scanf("%50s", name);
    send(new_socket, name, strlen(name), 0);
    printf("Waiting for other user...\n");
    valread = read(new_socket, otherName, sizeof(otherName));
    printf("Please enter a message (type q to quit):\n");

    while (1) {
        valread = read(new_socket, buffer, sizeof(buffer));
        printf("%s: %s\n", otherName, buffer);
        if (strcmp(buffer, END_STR) == 0) {
            closeConnection();
            return 0;
        }
        printf("%s: ", name);
        fflush(stdout);
        scanf("%1023s", buffer);
        if (buffer[0] == 'q' && strlen(buffer) == 1) {
            send(new_socket, END_STR, strlen(END_STR), 0);
            closeConnection();
            return 0;
        }
        send(new_socket, buffer, strlen(buffer), 0);
        printf("Message delivered!\n");
        memset(buffer, 0, strlen(buffer));
    }
    return 0;
}

void closeConnection() {
    printf("Closing connection");
    for (int i = 0; i < 3; i++) {
        fflush(stdout);
        usleep(500000);
        printf(".");
    }
    fflush(stdout);
    sleep(1);
    printf("\nConnection closed!\n");
}