#ifndef SERVER_H
#define SERVER_H
#include <functional>
#include <thread>
#include <atomic>
class Server {
public:
    Server(int port);
    ~Server();
    void start();
    void stop();
    void handleClient(int clientSocket);
    void setHandler(std::function<void(int)> handler);
private:
    int port;
    int serverSocket;
    std::atomic<bool> running;
    std::thread serverThread;
    std::function<void(int)> clientHandler;
    void acceptLoop();
};
#endif
