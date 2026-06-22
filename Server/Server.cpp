#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <sstream>
#include "DataStore.h"
#include <thread>
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

DataStore store;


void HandleClient(SOCKET clientSocket, DataStore& store)
{
    while (true)
    {
        std::string command = recvMsg(clientSocket);
        if (command.empty())
        {
            std::cout << "[SERVER] Client disconnected.\n";
            break;
        }

        std::cout << "[SERVER] Received: " << command << std::endl;

        std::stringstream ss(command);
        std::string action;
        ss >> action;

        std::string response;

        if (action == "SET")
        {
            std::string key, value;
            ss >> key >> value;
            store.set(key, value);
            response = "OK";
        }
        else if (action == "GET")
        {
            std::string key;
            ss >> key;
            response = store.get(key);
        }
        else if (action == "DEL")
        {
            std::string key;
            ss >> key;
            response = store.del(key) ? "OK" : "NOT FOUND";
        }
        else if (action == "EXIT")
        {
            sendMsg(clientSocket, "BYE");
            break;
        }
        else
        {
            response = "UNKNOWN COMMAND";
        }

        sendMsg(clientSocket, response);
    }
    closesocket(clientSocket);

}
int main()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cout << "[SERVER] WSAStartup failed\n";
        return 1;
    }

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET)
    {
        std::cout << "[SERVER] Socket creation failed\n";
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(54000);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        std::cout << "[SERVER] Bind failed. Error: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        std::cout << "[SERVER] Listen failed. Error: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "[SERVER] Server started on port 54000...\n";
    std::cout << "[SERVER] Waiting for client...\n";

    while (true)
    {
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);

        if (clientSocket == INVALID_SOCKET)
        {
            std::cout << "[SERVER] Accept failed.\n";
            continue;
        }

        std::cout << "[SERVER] Client connected!\n";

        std::thread(
            HandleClient,
            clientSocket,
            std::ref(store)
        ).detach();
    }
 
 
}