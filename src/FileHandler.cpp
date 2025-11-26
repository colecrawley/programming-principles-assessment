#include "FileHandler.h"
#include <fstream>
#include <stdexcept>

/**
 * TODO: Implement file reading functionality
 * 
 * This method should read the entire contents of a file into a vector of chars.
 * 
 * Important considerations:
 * - Open the file in binary mode to handle all types of data
 * - Check if the file was opened successfully
 * - Throw std::runtime_error with a descriptive message if file cannot be opened
 * - Read all bytes from the file into a vector
 * 
 * Hint: Use std::ifstream with std::ios::binary flag
 * Hint: Use std::istreambuf_iterator to read the file contents
 * 
 * @param filename The path to the file to read
 * @return A vector containing the file's contents
 * @throws std::runtime_error if the file cannot be opened
 */
std::vector<char> FileHandler::readFile(const std::string& filename) {
    // opening the file in bin mode
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    
    // checks
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for reading: " + filename);
    }
    
    // check file suze
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    
    // read file into a vector
    std::vector<char> buffer(size);
    if (!file.read(buffer.data(), size)) {
        throw std::runtime_error("Failed to read file: " + filename);
    }
    
    return buffer;
}

/**
 * TODO: Implement file writing functionality
 * 
 * This method should write a vector of chars to a file.
 * 
 * Important considerations:
 * - Open the file in binary mode to preserve all data exactly
 * - Check if the file was opened successfully for writing
 * - Throw std::runtime_error with a descriptive message if file cannot be opened
 * - Write all bytes from the vector to the file
 * 
 * Hint: Use std::ofstream with std::ios::binary flag
 * Hint: Use the write() method with proper type casting
 * 
 * @param filename The path to the file to write
 * @param data The data to write to the file
 * @throws std::runtime_error if the file cannot be opened for writing
 */
void FileHandler::writeFile(const std::string& filename, const std::vector<char>& data) {
    // opening file in bin mode
    std::ofstream file(filename, std::ios::binary);
    
    // checks
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for writing: " + filename);
    }
    
    // writing
    file.write(data.data(), data.size());
    
    // write errors?
    if (!file.good()) {
        throw std::runtime_error("Failed to write file: " + filename);
    }
}
