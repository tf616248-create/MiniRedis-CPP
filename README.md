# MiniRedis-CPP

A lightweight Redis-inspired key-value server built in C++ using WinSock and TCP sockets.

## Features

- TCP client-server communication
- In-memory key-value storage
- Supports the following commands:
  - `SET key value`
  - `GET key`
  - `DEL key`
  - `EXIT`
- Built with Visual Studio and WinSock

## Technologies

- C++
- WinSock2
- TCP/IP
- STL (`unordered_map`)
- Client/Server Architecture

## Project Structure

```
MiniRedis
├── Server
├── Client
└── MiniRedis.sln
```

## Example

Client:

```text
SET name Tehila
OK

GET name
Tehila

DEL name
OK

GET name
NOT FOUND

EXIT
BYE
```

## How to Run

1. Open `MiniRedis.sln` in Visual Studio.
2. Build the solution.
3. Run the Server project.
4. Run the Client project.
5. Start sending commands.