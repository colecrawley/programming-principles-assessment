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
    return false;
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
    return false;
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
    return {};
}
