#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include <vector>
class Client {
public:
    Client(const std::string& host, int port);
    ~Client();
    bool connect();
    void disconnect();
    bool sendData(const std::vector<char>& data);
    std::vector<char> receiveData(size_t maxSize = 4096);
private:
    std::string host;
    int port;
    int clientSocket;
    bool connected;
};
#endif
