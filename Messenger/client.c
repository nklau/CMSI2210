#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 8080
#define END_STR "cya"

void closeConnection();

int main(int argc, char const *argv[]) {
   int sock = 0, valread;
   struct sockaddr_in serv_addr;
   char buffer[1024] = {0};
   char name[50] = {0};
   char otherName[50] = {0};

   if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
       printf("\n Socket creation error \n");
       return -1;
   }

   serv_addr.sin_family = AF_INET;
   serv_addr.sin_port = htons(PORT);

   if( inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) { //10.0.1.163
       printf("\nInvalid address or Address not supported \n");
       return -1;
   }

   if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
       printf("\nConnection Failed \n");
       return -1;
   }

   printf("What is your name? ");
   fflush(stdout);
   scanf("%50s", name);
   send(sock, name, strlen(name), 0);
   printf("Waiting for other user...\n");
   valread = read(sock, otherName, sizeof(otherName));
   printf("Please enter a message (type 'q' to quit):\n");

   while (1) {
        printf("%s: ", name);
        fflush(stdout);
        scanf("%1023s", buffer);
        if (buffer[0] == 'q' && strlen(buffer) == 1) {
            send(sock, END_STR, strlen(END_STR), 0);
            closeConnection();
            return 0;
        }
        send(sock, buffer, strlen(buffer), 0);
        printf("Message delivered!\n");
        memset(buffer, 0, strlen(buffer));
        valread = read(sock, buffer, sizeof(buffer));
        if (strcmp(buffer, END_STR) == 0) {
            closeConnection();
            return 0;
        }
        printf("%s: %s\n", otherName, buffer);
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