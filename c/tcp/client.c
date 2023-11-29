#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "Ws2_32.lib")

int main() {
    WSADATA wsaData;
    SOCKET sockfd;
    struct sockaddr_in serv_addr;
    int portno = 12345;  // Server port number
    char buffer[256];
    int n;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Failed to initialize Winsock: %d\n", WSAGetLastError());
        return 1;
    }

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd == INVALID_SOCKET) {
        printf("Error opening socket: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Define server address
    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Server IP
    serv_addr.sin_port = htons(portno);

    // Connect to server
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Error connecting: %d\n", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    // Send and receive data
    printf("Please enter the message: ");
    memset(buffer, 0, 256);
    fgets(buffer, 255, stdin);
    n = send(sockfd, buffer, strlen(buffer), 0);
    if (n < 0) {
        printf("Error writing to socket: %d\n", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    memset(buffer, 0, 256);
    n = recv(sockfd, buffer, 255, 0);
    if (n < 0) {
        printf("Error reading from socket: %d\n", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }
    printf("Server reply: %s\n", buffer);

    // Close the socket and clean up
    closesocket(sockfd);
    WSACleanup();
    return 0;
}
