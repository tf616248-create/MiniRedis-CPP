# MiniRedis-CPP

A lightweight Redis-inspired key-value server built in C++ using WinSock and TCP sockets.

## Features

* TCP client-server communication
* In-memory key-value storage
* Multi-client support using threads
* Thread-safe data access using mutexes
* Key expiration (TTL)
* Supports the following commands:

  * `SET key value`
  * `SET key value EX seconds`
  * `GET key`
  * `DEL key`
  * `EXIT`

## Technologies

* C++
* WinSock2
* TCP/IP
* STL (`unordered_map`)
* Multithreading (`std::thread`)
* Synchronization (`std::mutex`)
* Client/Server Architecture

## Architecture

### Multi-Client Support

The server can handle multiple clients simultaneously.

Each incoming connection is processed in a dedicated worker thread:

```text
Client 1 -> Thread #1
Client 2 -> Thread #2
Client 3 -> Thread #3
```

### Thread Safety

The shared datastore is protected using `std::mutex` and `std::lock_guard` to prevent race conditions when multiple clients access the database concurrently.

### TTL (Time To Live)

Keys can be configured to expire automatically after a specified number of seconds.

Example:

```text
SET session abc123 EX 10
```

After 10 seconds:

```text
GET session
NOT FOUND
```

## Project Structure

```text
MiniRedis
├── Server
├── Client
├── DataStore
└── MiniRedis.sln
```

## Example Session

```text
SET name Tehila
OK

GET name
Tehila

SET token xyz EX 5
OK

GET token
xyz

(wait 5 seconds)

GET token
NOT FOUND

DEL name
OK

EXIT
BYE
```

## How to Run

1. Open `MiniRedis.sln` in Visual Studio.
2. Build the solution.
3. Run the Server project.
4. Run one or more Client instances.
5. Start sending commands.

## Future Improvements

* Persistent storage (COMMIT / LOAD)
* Background snapshots
* Authentication
* Publish / Subscribe
* LRU Cache
* Thread Pool
* Replication
* Transaction Support
