#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "CompressionAlgorithm.h"
#include <vector>
#include <map>
#include <memory>

// node struct
struct HuffmanNode {
    char data;
    unsigned frequency;
    std::shared_ptr<HuffmanNode> left;
    std::shared_ptr<HuffmanNode> right;
    
    HuffmanNode(char data, unsigned freq) 
        : data(data), frequency(freq), left(nullptr), right(nullptr) {}
    
    HuffmanNode(unsigned freq, std::shared_ptr<HuffmanNode> l, std::shared_ptr<HuffmanNode> r)
        : data('\0'), frequency(freq), left(l), right(r) {}
};

class Huffman : public CompressionAlgorithm {
public:
    std::vector<char> compress(const std::vector<char>& data) override;
    std::vector<char> decompress(const std::vector<char>& data) override;

private:
    // helper funcs
    std::map<char, unsigned> calculateFrequencies(const std::vector<char>& data);
    std::shared_ptr<HuffmanNode> buildHuffmanTree(const std::map<char, unsigned>& frequencies);
    void generateCodes(std::shared_ptr<HuffmanNode> root, const std::string& code, 
                       std::map<char, std::string>& huffmanCodes);
    
    // encode and decode
    std::vector<char> encodeData(const std::vector<char>& data, 
                                 const std::map<char, std::string>& huffmanCodes);
    std::vector<char> decodeData(const std::vector<char>& encodedData, 
                                 std::shared_ptr<HuffmanNode> root, size_t originalSize);
    
    // serialization
    void serializeTree(std::shared_ptr<HuffmanNode> node, std::vector<char>& output);
    std::shared_ptr<HuffmanNode> deserializeTree(const std::vector<char>& data, size_t& index);
};

#endif