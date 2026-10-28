#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define PORT 1109
#define BUFFER_SIZE 512

void run_server(void)
{
    SOCKET server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    int addr_len = sizeof(client_addr);
    char buff[BUFFER_SIZE];
    int n;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd == INVALID_SOCKET) {
        printf("Socket creation failed.\n");
        return;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(server_fd, (struct sockaddr *)&server_addr,
             sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Bind failed. Error: %d\n", WSAGetLastError());
        closesocket(server_fd);
        return;
    }

    if (listen(server_fd, 5) == SOCKET_ERROR) {
        printf("Listen failed.\n");
        closesocket(server_fd);
        return;
    }

    printf("[SERVER] Waiting for client on port %d...\n", PORT);

    client_fd = accept(server_fd,
                       (struct sockaddr *)&client_addr,
                       &addr_len);

    if (client_fd == INVALID_SOCKET) {
        printf("Accept failed.\n");
        closesocket(server_fd);
        return;
    }

    printf("[SERVER] Client connected!\n");

    while (1) {
        memset(buff, 0, sizeof(buff));

        n = recv(client_fd, buff, BUFFER_SIZE - 1, 0);

        if (n <= 0) {
            printf("[SERVER] Client disconnected.\n");
            break;
        }

        buff[n] = '\0';
        printf("\n[CLIENT]: %s\n", buff);

        if (strcmp(buff, "x") == 0)
            break;

        printf("[SERVER] Enter reply: ");
        fflush(stdout);

        if (fgets(buff, sizeof(buff), stdin) == NULL)
            break;

        buff[strcspn(buff, "\r\n")] = '\0';

        if (send(client_fd, buff, (int)strlen(buff) + 1, 0)
            == SOCKET_ERROR) {
            printf("Sending failed.\n");
            break;
        }

        if (strcmp(buff, "x") == 0)
            break;
    }

    closesocket(client_fd);
    closesocket(server_fd);
}

void run_client(void)
{
    SOCKET client_fd;
    struct sockaddr_in server_addr;
    char buff[BUFFER_SIZE];
    int n;

    client_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (client_fd == INVALID_SOCKET) {
        printf("Socket creation failed.\n");
        return;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(client_fd, (struct sockaddr *)&server_addr,
                sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Connection failed. Start the server first.\n");
        closesocket(client_fd);
        return;
    }

    printf("[CLIENT] Connected to server!\n");

    while (1) {
        memset(buff, 0, sizeof(buff));

        printf("\n[CLIENT] Enter message (x to exit): ");
        fflush(stdout);

        if (fgets(buff, sizeof(buff), stdin) == NULL)
            break;

        buff[strcspn(buff, "\r\n")] = '\0';

        if (send(client_fd, buff, (int)strlen(buff) + 1, 0)
            == SOCKET_ERROR) {
            printf("Sending failed.\n");
            break;
        }

        if (strcmp(buff, "x") == 0)
            break;

        n = recv(client_fd, buff, BUFFER_SIZE - 1, 0);

        if (n <= 0) {
            printf("[CLIENT] Server disconnected.\n");
            break;
        }

        buff[n] = '\0';
        printf("[SERVER]: %s\n", buff);

        if (strcmp(buff, "x") == 0)
            break;
    }

    closesocket(client_fd);
}

int main(void)
{
    WSADATA wsa;
    int choice;

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Winsock initialization failed.\n");
        return 1;
    }

    printf("===== TCP CHAT PROGRAM =====\n");
    printf("1. Server\n");
    printf("2. Client\n");
    printf("Enter choice: ");

    if (scanf("%d", &choice) != 1) {
        printf("Invalid choice.\n");
        WSACleanup();
        return 1;
    }

    getchar();

    if (choice == 1)
        run_server();
    else if (choice == 2)
        run_client();
    else
        printf("Choose 1 or 2.\n");

    WSACleanup();
    return 0;
}
