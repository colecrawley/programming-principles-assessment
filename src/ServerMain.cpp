#include "Server.h"
#include "RLECompression.h"
#include "huffman.h"
#include <iostream>
#include <unistd.h>
#include <vector>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    Server server(8080);

    server.setHandler([](int clientSock) {
        auto recvExact = [&](int sock, std::vector<char>& buffer, size_t len) -> bool {
            buffer.resize(len);
            size_t received = 0;
            while (received < len) {
                int r = read(sock, buffer.data() + received, len - received);
                if (r <= 0) return false;
                received += r;
            }
            return true;
        };

        auto recvWithLength = [&](std::vector<char>& buffer) -> bool {
            std::vector<char> lenBuf;
            if (!recvExact(clientSock, lenBuf, sizeof(uint32_t))) return false;
            uint32_t netLen;
            std::memcpy(&netLen, lenBuf.data(), sizeof(netLen));
            uint32_t len = ntohl(netLen);
            return recvExact(clientSock, buffer, len);
        };

        // process one response at a time
        // receive
        std::vector<char> opBuf;
        if (!recvWithLength(opBuf)) { close(clientSock); return; }
        std::string operation(opBuf.begin(), opBuf.end());

        std::vector<char> algoBuf;
        if (!recvWithLength(algoBuf)) { close(clientSock); return; }
        std::string algoName(algoBuf.begin(), algoBuf.end());

        CompressionAlgorithm* algo = nullptr;
        if (algoName == "rle") algo = new RLECompression();
        else if (algoName == "huffman") algo = new Huffman();
        else { std::cerr << "Unknown algorithm\n"; close(clientSock); return; }

        // receiving the data
        std::vector<char> data;
        if (!recvWithLength(data)) { delete algo; close(clientSock); return; }

        // process
        std::vector<char> result;
        if (operation == "compress") {
            result = algo->compress(data);
            std::cout << "Server: Compressed " << data.size() << " bytes to " << result.size() << " bytes\n";
        }
        else if (operation == "decompress") {
            result = algo->decompress(data);
            std::cout << "Server: Decompressed " << data.size() << " bytes to " << result.size() << " bytes\n";
        }

        // send
        uint32_t sendLen = htonl(result.size());
        send(clientSock, &sendLen, sizeof(sendLen), 0);
        send(clientSock, result.data(), result.size(), 0);

        delete algo;
        close(clientSock);
    });

    std::cout << "Server listening on port 8080\n";
    server.start();

    std::string input;
    std::cout << "Press Enter to stop server...\n";
    std::getline(std::cin, input);

    server.stop();
    return 0;
}