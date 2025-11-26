#include "Client.h"
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

/**
 * Client constructor - Initialize member variables
 * This is already implemented for you.
 */
Client::Client(const std::string& host, int port) 
    : host(host), port(port), clientSocket(-1), connected(false) {}

/**
 * Client destructor - Clean up resources
 * This is already implemented for you.
 */
Client::~Client() {
    disconnect();
}

/**
 * TODO: Implement TCP socket connection to server
 * 
 * This method should establish a TCP connection to the server specified by host and port.
 * 
 * Important considerations:
 * - Check if already connected (return true if so)
 * - Create a TCP socket using socket(AF_INET, SOCK_STREAM, 0)
 * - Set up sockaddr_in structure with server address and port
 * - Use inet_pton() to convert IP address string to binary form
 * - Call ::connect() to establish connection
 * - Handle errors gracefully: close socket and return false on failure
 * - Update connected flag and return true on success
 * 
 * Hint: Use htons() to convert port to network byte order
 * Hint: Check return values of socket(), inet_pton(), and connect()
 * 
 * @return true if connection successful, false otherwise
 */
bool Client::connect() {
    // TODO: Implement connection logic here
    // Your implementation goes here

    if (connected) {
        return true;
    }
    
    // Create TCP socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return false;
    }
    
    // Set up server address
    sockaddr_in serverAddr;
    std::memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    
    // Convert IP address from string to binary
    if (inet_pton(AF_INET, host.c_str(), &serverAddr.sin_addr) <= 0) {
        std::cerr << "Invalid address / Address not supported" << std::endl;
        close(clientSocket);
        clientSocket = -1;
        return false;
    }
    
    // Connect to server
    if (::connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        close(clientSocket);
        clientSocket = -1;
        return false;
    }
    
    connected = true;
    return true;
}

/**
 * TODO: Implement socket disconnection
 * 
 * This method should close the socket and clean up the connection.
 * 
 * Important considerations:
 * - Check if connected before attempting to close
 * - Close the socket using close()
 * - Reset clientSocket to -1
 * - Set connected flag to false
 * 
 * @return void
 */
void Client::disconnect() {
    // TODO: Implement disconnection logic here
    // Your implementation goes here

    if (connected && clientSocket >= 0) {
        close(clientSocket);
        clientSocket = -1;
        connected = false;
    }
}

/**
 * TODO: Implement sending data over the socket
 * 
 * This method should send the provided data through the connected socket.
 * 
 * Important considerations:
 * - Check if connected before attempting to send
 * - Use send() system call to transmit data
 * - Verify that all bytes were sent successfully
 * - Return true only if all data was sent, false otherwise
 * 
 * Hint: Compare bytes sent with data.size()
 * 
 * @param data The data to send
 * @return true if all data sent successfully, false otherwise
 */
bool Client::sendData(const std::vector<char>& data) {
    // TODO: Implement data sending logic here
    // Your implementation goes here

    // double check its connected still
    if (!connected || clientSocket < 0) {
        std::cerr << "Not connected to server" << std::endl;
        return false;
    }
    
    size_t totalSent = 0;
    const char* ptr = data.data();

    // send the data
    while (totalSent < data.size()) {
        ssize_t bytesSent = send(clientSocket, 
                                  ptr + totalSent, 
                                  data.size() - totalSent, 
                                  0);
    
    // double check the sent data
    if (bytesSent < 0) {
        std::cerr << "Failed to send data" << std::endl;
        return false;
    }
    
    if (bytesSent == 0) {
            std::cerr << "Connection closed during send" << std::endl;
            return false;
        }
        
        totalSent += bytesSent;
    }
    
    return true;
}

/**
 * TODO: Implement receiving data from the socket
 * 
 * This method should receive data from the connected socket.
 * 
 * Important considerations:
 * - Check if connected before attempting to receive
 * - Create a buffer of maxSize to store received data
 * - Use read() or recv() to receive data from socket
 * - Handle cases where bytes <= 0 (error or connection closed)
 * - Resize the buffer to actual number of bytes received
 * - Return empty vector on error
 * 
 * @param maxSize Maximum number of bytes to receive (default 4096)
 * @return Vector containing received data, or empty vector on error
 */
std::vector<char> Client::receiveData(size_t maxSize) {
    // TODO: Implement data receiving logic here
    // Your implementation goes here

    std::vector<char> buffer;
    
    // Check if connected
    if (!connected || clientSocket < 0) {
        std::cerr << "Not connected to server" << std::endl;
        return buffer;
    }
    
    // Prepare buffer
    buffer.resize(maxSize);
    
    // Receive data
    ssize_t bytesRead = read(clientSocket, buffer.data(), maxSize);
    
    // Handle errors
    if (bytesRead < 0) {
        std::cerr << "Failed to receive data" << std::endl;
        buffer.clear();
        return buffer;
    }
    
    if (bytesRead == 0) {
        // Connection closed by server
        buffer.clear();
        return buffer;
    }
    
    // Resize buffer to actual bytes received
    buffer.resize(bytesRead);
    
    return buffer;
}
