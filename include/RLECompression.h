#ifndef RLE_COMPRESSION_H
#define RLE_COMPRESSION_H
#include "CompressionAlgorithm.h"
#include <vector>
class RLECompression : public CompressionAlgorithm {
public:
    std::vector<char> compress(const std::vector<char>& data) override;
    std::vector<char> decompress(const std::vector<char>& data) override;
};
#endif
