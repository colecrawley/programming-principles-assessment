#include "Client.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <cstring>
#include <arpa/inet.h>
#include <fstream>
#include <filesystem>

int main() {
    std::string algoName;
    std::cout << "Enter algorithm (rle or huffman): ";
    std::cin >> algoName;

    std::vector<char> data{'A','A','A','A','A','B','B','B','B','C','C','C','C','D'};
    std::cout << "Original data: ";
    for (char c : data) std::cout << c;
    std::cout << " (" << data.size() << " bytes)\n";

    // create dir if it doesnt exist
    std::filesystem::create_directory("compress");
    std::filesystem::create_directory("decompress");

    // convert string to vector char
    auto stringToVector = [](const std::string& str) {
        return std::vector<char>(str.begin(), str.end());
    };

    // help func to save vector file
    auto saveToFile = [](const std::vector<char>& data, const std::string& filename) {
        std::ofstream file(filename, std::ios::binary);
        if (file) {
            file.write(data.data(), data.size());
            std::cout << "Saved: " << filename << " (" << data.size() << " bytes)\n";
        } else {
            std::cerr << "Failed to save: " << filename << "\n";
        }
    };

    // comp with diff connection
    {
        Client client("127.0.0.1", 8080);
        if (!client.connect()) {
            std::cerr << "Failed to connect to server for compression\n";
            return 1;
        }

        auto sendWithLength = [&](const std::vector<char>& buf) {
            uint32_t len = htonl(buf.size());
            client.sendData(std::vector<char>(reinterpret_cast<char*>(&len),
                                              reinterpret_cast<char*>(&len) + sizeof(len)));
            client.sendData(buf);
        };

        auto recvWithLength = [&]() -> std::vector<char> {
            std::vector<char> lenBuf = client.receiveData(sizeof(uint32_t));
            if (lenBuf.size() != sizeof(uint32_t)) return {};
            uint32_t netLen;
            std::memcpy(&netLen, lenBuf.data(), sizeof(netLen));
            uint32_t len = ntohl(netLen);
            return client.receiveData(len);
        };

        std::cout << "Compressing...\n";
        sendWithLength(stringToVector("compress"));
        sendWithLength(stringToVector(algoName));
        sendWithLength(data);

        auto compressed = recvWithLength();
        std::cout << "Compressed size: " << compressed.size() << " bytes\n";

        // save
        std::string compressedFilename = "compress/original_" + algoName + ".bin";
        saveToFile(compressed, compressedFilename);

        client.disconnect();

        // decomp with a diff connection
        Client client2("127.0.0.1", 8080);
        if (!client2.connect()) {
            std::cerr << "Failed to connect to server for decompression\n";
            return 1;
        }

        auto sendWithLength2 = [&](const std::vector<char>& buf) {
            uint32_t len = htonl(buf.size());
            client2.sendData(std::vector<char>(reinterpret_cast<char*>(&len),
                                               reinterpret_cast<char*>(&len) + sizeof(len)));
            client2.sendData(buf);
        };

        auto recvWithLength2 = [&]() -> std::vector<char> {
            std::vector<char> lenBuf = client2.receiveData(sizeof(uint32_t));
            if (lenBuf.size() != sizeof(uint32_t)) return {};
            uint32_t netLen;
            std::memcpy(&netLen, lenBuf.data(), sizeof(netLen));
            uint32_t len = ntohl(netLen);
            return client2.receiveData(len);
        };

        std::cout << "Decompressing...\n";
        sendWithLength2(stringToVector("decompress"));
        sendWithLength2(stringToVector(algoName));
        sendWithLength2(compressed);

        auto decompressed = recvWithLength2();
        std::string out(decompressed.begin(), decompressed.end());
        std::cout << "Decompressed content: " << out << " (" << decompressed.size() << " bytes)\n";

        // saving in a dir
        std::string decompressedFilename = "decompress/decompressed_" + algoName + ".txt";
        saveToFile(decompressed, decompressedFilename);

        client2.disconnect();
    }

    return 0;
}