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
    std::vector<char> out;
    // Your implementation goes here
    return out;
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
    // TODO: Implement decompression logic here
    std::vector<char> out;
    // Your implementation goes here
    return out;
}
