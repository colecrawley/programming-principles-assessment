#include "Server.h"
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

/**
 * Server constructor - Initialize member variables
 * This is already implemented for you.
 */
Server::Server(int port) : port(port), serverSocket(-1), running(false) {}

/**
 * Server destructor - Clean up resources
 * This is already implemented for you.
 */
Server::~Server() {
    stop();
}

/**
 * TODO: Implement server startup and socket binding
 * 
 * This method should start the server by creating a socket, binding it to a port,
 * and starting to listen for connections.
 * 
 * Important considerations:
 * - Check if already running (return early if so)
 * - Create a TCP socket using socket(AF_INET, SOCK_STREAM, 0)
 * - Set SO_REUSEADDR socket option to allow quick restart
 * - Bind socket to INADDR_ANY on the specified port
 * - Start listening with a reasonable backlog (e.g., 8)
 * - Set running flag to true
 * - Start acceptLoop in a separate thread (use std::thread)
 * - Throw std::runtime_error with descriptive message on failure
 * 
 * Hint: Use htons() for port conversion
 * Hint: Check return values and throw exceptions on errors
 * 
 * @throws std::runtime_error if socket creation, binding, or listening fails
 */
void Server::start() {
    // TODO: Implement server start logic here
    // Your implementation goes here

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
         throw std::runtime_error("Server::start not implemented");
    }

    // quick start
    int opt = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        close(serverSocket);
        throw std::runtime_error("Failed to set SO_REUSEADDR");
    }
    
    // bind socket to the address
    sockaddr_in serverAddr;
    std::memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);
    
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        close(serverSocket);
        throw std::runtime_error("Failed to bind socket to port " + std::to_string(port));
    }
    
    // listening
    if (listen(serverSocket, 8) < 0) {
        close(serverSocket);
        throw std::runtime_error("Failed to listen on socket");
    }
    
    // run flag
    running = true;
    
    // accept loop
    serverThread = std::thread(&Server::acceptLoop, this);
}

/**
 * TODO: Implement server shutdown
 * 
 * This method should gracefully stop the server and clean up resources.
 * 
 * Important considerations:
 * - Check if server is running (return early if not)
 * - Set running flag to false to signal threads to stop
 * - Shutdown and close the server socket
 * - Wait for serverThread to finish (use join() if joinable)
 * - Reset serverSocket to -1
 * 
 * Hint: Use shutdown(serverSocket, SHUT_RDWR) before close()
 * 
 * @return void
 */
void Server::stop() {
    // TODO: Implement server stop logic here
    // Your implementation goes here

    if (!running) {
        return;
    }
    
    // signal thread
    running = false;
    
    // close server
    if (serverSocket >= 0) {
        shutdown(serverSocket, SHUT_RDWR);
        close(serverSocket);
        serverSocket = -1;
    }
    
    // wait for accept thread
    if (serverThread.joinable()) {
        serverThread.join();
    }
}

/**
 * TODO: Implement client connection handler
 * 
 * This method handles communication with a single client.
 * 
 * Important considerations:
 * - If a custom clientHandler is set, use it
 * - Otherwise, implement default echo behavior:
 *   - Read data from the client socket
 *   - Send the same data back (echo)
 *   - Close the client socket when done
 * - Handle errors gracefully
 * 
 * Hint: Use read() to receive data and send() to transmit
 * Hint: Always close the client socket when done
 * 
 * @param clientSocket The socket descriptor for the connected client
 */
void Server::handleClient(int clientSocket) {
    // TODO: Implement client handling logic here
    // Your implementation goes here

    if (clientHandler) {
        clientHandler(clientSocket);
        return;
    }
    
    // echo behaviour
    char buffer[4096];
    ssize_t bytesRead = read(clientSocket, buffer, sizeof(buffer));
    
    if (bytesRead > 0) {
        // echo back to client
        send(clientSocket, buffer, bytesRead, 0);
    }

    close(clientSocket);
}

/**
 * Set a custom handler function for client connections
 * This is already implemented for you.
 */
void Server::setHandler(std::function<void(int)> handler) {
    clientHandler = handler;
}

/**
 * TODO: Implement accept loop for incoming connections
 * 
 * This is the main server loop that accepts new client connections.
 * 
 * Important considerations:
 * - Loop while running flag is true
 * - Use accept() to wait for and accept new client connections
 * - Handle accept() errors appropriately (check running flag)
 * - For each accepted connection, create a new detached thread to handle the client
 * - Use std::thread with handleClient method
 * - Detach the thread so it runs independently
 * 
 * Hint: Check if running is still true after accept() fails
 * Hint: Use std::thread(&Server::handleClient, this, clientSocket).detach()
 * 
 * @return void (runs in separate thread until server stops)
 */
void Server::acceptLoop() {
    // TODO: Implement accept loop logic here
    // Your implementation goes here

    while (running) {
        sockaddr_in clientAddr;
        socklen_t clientLen = sizeof(clientAddr);
        
        // accept connection
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientLen);
        
        if (clientSocket < 0) {
            // check is the server is running
            if (!running) {
                break;
            }
            std::cerr << "Failed to accept client connection" << std::endl;
            continue;
        }
        
        // handle client in different thread
        std::thread(&Server::handleClient, this, clientSocket).detach();
    }
}
