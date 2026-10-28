// lws2_32
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
    SOCKET server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    int client_size;
    char buffer[BUFFER_SIZE];

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("WSAStartup failed.\n");
        return 1;
    }

    printf("Winsock initialized.\n");

    // SOCKET primitive
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket == INVALID_SOCKET)
    {
        printf("Socket creation failed.\n");
        WSACleanup();
        return 1;
    }

    printf("Server socket created.\n");

    // Server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // BIND primitive
    if (bind(server_socket,
             (struct sockaddr *)&server_addr,
             sizeof(server_addr)) == SOCKET_ERROR)
    {
        printf("Bind failed.\n");
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    printf("Server bound to port %d.\n", PORT);

    // LISTEN primitive
    if (listen(server_socket, 5) == SOCKET_ERROR)
    {
        printf("Listen failed.\n");
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    printf("Server is waiting for client...\n");

    // ACCEPT primitive
    client_size = sizeof(client_addr);

    client_socket = accept(
        server_socket,
        (struct sockaddr *)&client_addr,
        &client_size);

    if (client_socket == INVALID_SOCKET)
    {
        printf("Accept failed.\n");
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    printf("Client connected!\n");

    // Chat
    while (1)
    {
        memset(buffer, 0, BUFFER_SIZE);

        // RECEIVE primitive
        recv(client_socket, buffer, BUFFER_SIZE - 1, 0);

        printf("Client: %s\n", buffer);

        if (strcmp(buffer, "exit") == 0)
            break;

        printf("Server: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        buffer[strcspn(buffer, "\n")] = '\0';

        // SEND primitive
        send(client_socket, buffer, strlen(buffer) + 1, 0);

        if (strcmp(buffer, "exit") == 0)
            break;
    }

    // CLOSE primitive
    closesocket(client_socket);
    closesocket(server_socket);

    WSACleanup();

    printf("Connection closed.\n");

    return 0;
}
