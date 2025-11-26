#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H
#include <string>
#include <vector>
class FileHandler {
public:
    static std::vector<char> readFile(const std::string& filename);
    static void writeFile(const std::string& filename, const std::vector<char>& data);
};
#endif
