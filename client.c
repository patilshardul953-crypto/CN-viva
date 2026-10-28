#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    WSADATA wsa;
    SOCKET client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("WSAStartup failed.\n");
        return 1;
    }

    printf("Winsock initialized.\n");

    // SOCKET primitive
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (client_socket == INVALID_SOCKET)
    {
        printf("Socket creation failed.\n");
        WSACleanup();
        return 1;
    }

    printf("Client socket created.\n");

    // Server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // CONNECT primitive
    if (connect(client_socket,
                (struct sockaddr *)&server_addr,
                sizeof(server_addr)) == SOCKET_ERROR)
    {
        printf("Connection failed.\n");
        closesocket(client_socket);
        WSACleanup();
        return 1;
    }

    printf("Connected to server!\n");

    // Chat
    while (1)
    {
        printf("Client: ");

        fgets(buffer, BUFFER_SIZE, stdin);

        buffer[strcspn(buffer, "\n")] = '\0';

        // SEND primitive
        send(client_socket, buffer, strlen(buffer) + 1, 0);

        if (strcmp(buffer, "exit") == 0)
            break;

        memset(buffer, 0, BUFFER_SIZE);

        // RECEIVE primitive
        recv(client_socket, buffer, BUFFER_SIZE - 1, 0);

        printf("Server: %s\n", buffer);

        if (strcmp(buffer, "exit") == 0)
            break;
    }

    // CLOSE primitive
    closesocket(client_socket);

    WSACleanup();

    printf("Connection closed.\n");

    return 0;
}

