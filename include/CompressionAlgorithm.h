#ifndef COMPRESSION_ALGORITHM_H
#define COMPRESSION_ALGORITHM_H
#include <vector>
class CompressionAlgorithm {
public:
    virtual ~CompressionAlgorithm() {}
    virtual std::vector<char> compress(const std::vector<char>& data) = 0;
    virtual std::vector<char> decompress(const std::vector<char>& data) = 0;
};
#endif
