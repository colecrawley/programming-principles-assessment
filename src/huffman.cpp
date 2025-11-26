#include "huffman.h"
#include <queue>
#include <stdexcept>
#include <bitset>
#include <cstring>

// comparator
struct CompareNode {
    bool operator()(const std::shared_ptr<HuffmanNode>& a, 
                    const std::shared_ptr<HuffmanNode>& b) {
        return a->frequency > b->frequency;
    }
};

// char frequency
std::map<char, unsigned> Huffman::calculateFrequencies(const std::vector<char>& data) {
    std::map<char, unsigned> frequencies;
    for (char c : data) {
        frequencies[c]++;
    }
    return frequencies;
}

// huffman tree
std::shared_ptr<HuffmanNode> Huffman::buildHuffmanTree(
    const std::map<char, unsigned>& frequencies) {
    
    std::priority_queue<std::shared_ptr<HuffmanNode>, 
                        std::vector<std::shared_ptr<HuffmanNode>>, 
                        CompareNode> pq;
    
    // leaf nodes
    for (const auto& pair : frequencies) {
        pq.push(std::make_shared<HuffmanNode>(pair.first, pair.second));
    }
    
    // build tree with nodes
    while (pq.size() > 1) {
        auto left = pq.top(); pq.pop();
        auto right = pq.top(); pq.pop();
        
        auto parent = std::make_shared<HuffmanNode>(
            left->frequency + right->frequency, left, right);
        pq.push(parent);
    }
    
    return pq.top();
}

// huffman codes by going through tree
void Huffman::generateCodes(std::shared_ptr<HuffmanNode> root, 
                                       const std::string& code, 
                                       std::map<char, std::string>& huffmanCodes) {
    if (!root) return;
    
    if (!root->left && !root->right) {
        huffmanCodes[root->data] = code.empty() ? "0" : code;
        return;
    }
    
    // go left and right
    generateCodes(root->left, code + "0", huffmanCodes);
    generateCodes(root->right, code + "1", huffmanCodes);
}

//serialize tree
void Huffman::serializeTree(std::shared_ptr<HuffmanNode> node, 
                                       std::vector<char>& output) {
    if (!node) return;
    
    if (!node->left && !node->right) {
        output.push_back(1);
        output.push_back(node->data);
    } else {
        output.push_back(0);
        serializeTree(node->left, output);
        serializeTree(node->right, output);
    }
}

// deserilize tree
std::shared_ptr<HuffmanNode> Huffman::deserializeTree(
    const std::vector<char>& data, size_t& index) {
    
    if (index >= data.size()) {
        throw std::runtime_error("Invalid Huffman tree data");
    }
    
    char marker = data[index++];
    
    if (marker == 1) {
        if (index >= data.size()) {
            throw std::runtime_error("Invalid Huffman tree data");
        }
        char ch = data[index++];
        return std::make_shared<HuffmanNode>(ch, 0);
    } else {
        auto left = deserializeTree(data, index);
        auto right = deserializeTree(data, index);
        return std::make_shared<HuffmanNode>(0, left, right);
    }
}

// encode data and turn to bytes
std::vector<char> Huffman::encodeData(
    const std::vector<char>& data, 
    const std::map<char, std::string>& huffmanCodes) {
    
    // bit string
    std::string bitString;
    for (char c : data) {
        bitString += huffmanCodes.at(c);
    }
    
    // convert to byte
    std::vector<char> encoded;
    for (size_t i = 0; i < bitString.size(); i += 8) {
        std::string byte = bitString.substr(i, 8);
        while (byte.size() < 8) {
            byte += '0';
        }
        encoded.push_back(static_cast<char>(std::bitset<8>(byte).to_ulong()));
    }
    
    return encoded;
}

// decode data
std::vector<char> Huffman::decodeData(
    const std::vector<char>& encodedData, 
    std::shared_ptr<HuffmanNode> root, 
    size_t originalSize) {
    
    std::vector<char> decoded;
    decoded.reserve(originalSize);
    
    auto current = root;
    size_t decodedCount = 0;
    
    for (char byte : encodedData) {
        for (int i = 7; i >= 0; --i) {
            bool bit = (byte >> i) & 1;
            
            // go through the tree
            current = bit ? current->right : current->left;
            
            if (!current->left && !current->right) {
                decoded.push_back(current->data);
                current = root;
                decodedCount++;
                
                // stop when all char decoded
                if (decodedCount >= originalSize) {
                    return decoded;
                }
            }
        }
    }
    
    return decoded;
}

// compress
std::vector<char> Huffman::compress(const std::vector<char>& data) {
    if (data.empty()) {
        return std::vector<char>();
    }
    
    if (data.size() == 1) {
        std::vector<char> result;
        size_t size = 1;
        result.insert(result.end(), 
                     reinterpret_cast<const char*>(&size), 
                     reinterpret_cast<const char*>(&size) + sizeof(size_t));
        // encoding
        result.push_back(1);
        result.push_back(data[0]);
        result.push_back(0);
        return result;
    }
    
    // calc frequency
    auto frequencies = calculateFrequencies(data);
    auto root = buildHuffmanTree(frequencies);
    
    // huffman codes
    std::map<char, std::string> huffmanCodes;
    generateCodes(root, "", huffmanCodes);
    
    auto encodedData = encodeData(data, huffmanCodes);
    
    // build output
    std::vector<char> compressed;
    
    size_t originalSize = data.size();
    compressed.insert(compressed.end(), 
                     reinterpret_cast<const char*>(&originalSize), 
                     reinterpret_cast<const char*>(&originalSize) + sizeof(size_t));
    
    serializeTree(root, compressed);
    
    compressed.insert(compressed.end(), encodedData.begin(), encodedData.end());
    
    return compressed;
}

// decompress
std::vector<char> Huffman::decompress(const std::vector<char>& data) {

    if (data.empty()) {
        return std::vector<char>();
    }
    
    // check min size
    if (data.size() < sizeof(size_t)) {
        throw std::runtime_error("Invalid Huffman compressed data: too short");
    }
    
    // get original size
    size_t originalSize;
    std::memcpy(&originalSize, data.data(), sizeof(size_t));
    
    // deserialize
    size_t index = sizeof(size_t);
    auto root = deserializeTree(data, index);
    
    // get encoded data
    std::vector<char> encodedData(data.begin() + index, data.end());
    
    // decoding
    return decodeData(encodedData, root, originalSize);
}