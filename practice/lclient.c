#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr*)&addr, sizeof(addr));

    char *msg = "Hello from client";
    send(sock, msg, strlen(msg), 0);

    close(sock);
}

//instead ofhardcoding 127.0.0.1
//getaddrinfo("localhost", "8080", &hints, &res);