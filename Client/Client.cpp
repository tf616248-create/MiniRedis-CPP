#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

bool sendMsg(SOCKET s, const std::string& msg)
{
    std::string data = msg + "\n";
    return send(s, data.c_str(), (int)data.size(), 0) != SOCKET_ERROR;
}

std::string recvMsg(SOCKET s)
{
    std::string result;
    char c;
    while (true)
    {
        int r = recv(s, &c, 1, 0);
        if (r <= 0) return "";
        if (c == '\n') return result;
        result += c;
    }
}

int main()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cout << "[CLIENT] WSAStartup failed\n";
        return 1;
    }

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET)
    {
        std::cout << "[CLIENT] Socket creation failed\n";
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(54000);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        std::cout << "[CLIENT] Connection failed. Error: " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "[CLIENT] Connected to server!\n";

    std::string command;
    while (true)
    {
        std::cout << "> ";
        std::getline(std::cin, command);

        sendMsg(clientSocket, command);

        std::string response = recvMsg(clientSocket);
        std::cout << response << std::endl;

        if (command == "EXIT")
            break;
    }

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}