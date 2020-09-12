#ifndef READER_HPP
#define READER_HPP


#include <stdint-gcc.h>
#include <string>
#include <filesystem>

#include "helpers.hpp"

class Reader {
private:
    uint64_t _blockSize;
    uint8_t _numOfJobs;
    bool _isCaching;

public:
    explicit Reader(uint64_t blockSize, uint8_t numOfJobs, bool isCaching);

    void readWithRead(const std::string &fileName) const;           // read (Linux)
    void readWithFread(const std::string &fileName) const;          // fread (Cross-Platform)
    void readWithIfstream(const std::string &fileName) const;       // ifstream (Cross-Platform)
    void readWithMmap(const std::string &fileName, bool shared) const;    // mmap (Cross-Platform)
#ifndef __linux__

    void readWithReadFile(const std::string &fileName) const;             // WinAPI (Windows)
#endif

};


#endif
