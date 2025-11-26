#include "RLECompression.h"
#include <stdexcept>

/**
 * TODO: Implement Run-Length Encoding compression
 * 
 * This method should compress the input data using the RLE algorithm.
 * RLE works by replacing consecutive repeated characters with a pair: the character and its count.
 * 
 * Format: For each run of identical characters, output [character, count]
 * 
 * Important considerations:
 * - Handle empty input (return empty vector)
 * - Count should be limited to 255 (use unsigned char for count)
 * - Process data in a single pass
 * 
 * Example: "aaabbc" → ['a',3, 'b',2, 'c',1]
 * 
 * @param data The input data to compress
 * @return The compressed data as a vector of chars
 */
std::vector<char> RLECompression::compress(const std::vector<char>& data) {
    // TODO: Implement compression logic here
    std::vector<char> compressed;
    // Your implementation goes here

    // handling empty input
    if (data.empty()) {
        return compressed;
    }
    
    // reserving space
    compressed.reserve(data.size());
    
    size_t i = 0;
    while (i < data.size()) {
        char currentByte = data[i];
        unsigned char count = 1;
        
        // counting consecutive bytes
        while (i + count < data.size() && 
               data[i + count] == currentByte && 
               count < 255) {
            count++;
        }
        
        compressed.push_back(static_cast<char>(count));
        compressed.push_back(currentByte);
        
        i += count;
    }
    
    return compressed;
}

/**
 * TODO: Implement Run-Length Encoding decompression
 * 
 * This method should decompress RLE-encoded data back to the original format.
 * 
 * Format: Input is pairs of [character, count] that need to be expanded.
 * 
 * Important considerations:
 * - Handle empty input (return empty vector)
 * - Validate that data has even length (each run needs character + count)
 * - Check for zero counts (invalid data)
 * - Expand each pair by repeating the character 'count' times
 * 
 * Example: ['a',3, 'b',2, 'c',1] → "aaabbc"
 * 
 * @param data The compressed data to decompress
 * @return The decompressed data as a vector of chars
 * @throws std::runtime_error if data is malformed (odd length or zero count)
 */
std::vector<char> RLECompression::decompress(const std::vector<char>& data) {
    std::vector<char> decompressed;
    
    // handling emtpy input
    if (data.empty()) {
        return decompressed;
    }
    
    // checking length
    if (data.size() % 2 != 0) {
        throw std::runtime_error("Invalid RLE data: odd number of bytes");
    }
    
    // validating input
    size_t estimatedSize = 0;
    for (size_t i = 0; i < data.size(); i += 2) {
        unsigned char count = static_cast<unsigned char>(data[i]);
        
        if (count == 0) {
            throw std::runtime_error("Invalid RLE data: zero count");
        }
        
        estimatedSize += count;
        
        // protection of too much memory
        if (estimatedSize > 1000000000) {
            throw std::runtime_error("RLE decompression would exceed memory limits");
        }
    }
    
    decompressed.reserve(estimatedSize);
    
    // decompress
    for (size_t i = 0; i < data.size(); i += 2) {
        unsigned char count = static_cast<unsigned char>(data[i]);
        char value = data[i + 1];
        
        for (unsigned char j = 0; j < count; j++) {
            decompressed.push_back(value);
        }
    }
    
    return decompressed;
}
