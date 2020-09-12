#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <fstream>
#include <iostream>
#include <cstring>
#ifndef __linux__
#include <w32api/fileapi.h>
#include <w32api/handleapi.h>

#endif
#include "../include/Reader.hpp"

Reader::Reader(uint64_t blockSize, uint8_t numOfJobs, bool isCaching) : _blockSize(blockSize), _numOfJobs(numOfJobs),
                                                                        _isCaching(isCaching) {}

void Reader::readWithRead(const std::string &fileName) const {
    int fd = open(fileName.c_str(), O_RDONLY);
    if (fd >= 0) {
        char *buffer = new char[this->_blockSize];
        while (read(fd, buffer, this->_blockSize)) {
        }
    } else
        std::cout << "read failed" << std::endl;
    close(fd);
}

void Reader::readWithFread(const std::string &fileName) const {
    FILE *fp = fopen(fileName.c_str(), "rb");
    if (fp != nullptr) {
        char *buffer = new char[this->_blockSize];
        uint64_t fileSize = getFileSize(fileName);
        while (ftell(fp) < fileSize) {
            fread(buffer, sizeof(char), this->_blockSize, fp);
        }
    } else
        std::cout << "fread failed!" << std::endl;
    fclose(fp);
}

void Reader::readWithIfstream(const std::string &fileName) const {
    std::ifstream inputStream(fileName, std::ios::binary);
    if (inputStream.is_open()) {
        char *buffer = new char[this->_blockSize];
        while (inputStream.read(buffer, this->_blockSize)) {
            inputStream.seekg(this->_blockSize, std::ifstream::cur);
        }
    } else {
        std::cout << "ifstream failed!" << std::endl;
    }
    inputStream.close();

}

void Reader::readWithMmap(const std::string &fileName, bool shared) {
    void *mmaped = nullptr, *temp = nullptr;
    int fd = open(fileName.c_str(), O_RDONLY, 0);
    uint64_t fileSize = getFileSize(fileName);
    char *buffer = new char[this->_blockSize];
    __off_t offset = 0;
#ifdef __linux__
    mmaped = mmap(nullptr, fileSize, PROT_READ, (shared?MAP_SHARED:MAP_PRIVATE) | MAP_POPULATE , fd, 0);
   if (mmaped == MAP_FAILED)
        std::cout << "mmap failed!" << std::endl;
    else {
        temp = mmaped;
        while (offset < fileSize) {
            memcpy(buffer, temp, this->_blockSize);
            offset += this->_blockSize;
            temp = static_cast<char *>(temp) + this->_blockSize;
        }
    }
#else
    mmaped = mmap(nullptr, fileSize, PROT_READ, (shared ? MAP_SHARED : MAP_PRIVATE), fd, 0);
    if (mmaped == MAP_FAILED)
        std::cout << "mmap failed!" << std::endl;
    else {
        temp = mmaped;
        while (offset < fileSize) {
            memcpy(buffer, temp, this->_blockSize);
            offset += this->_blockSize;
            temp = static_cast<char *>(temp) + this->_blockSize;
        }
    }
#endif

    close(fd);
}

#ifndef __linux__

void Reader::readWithReadFile(const std::string &fileName) {
    HANDLE fp =  CreateFile((LPCSTR) fileName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    TCHAR *buffer = new TCHAR [this->_blockSize];
    DWORD nRead = 0;
    uint64_t readBytes = 0;
    uint64_t fileSize = getFileSize(fileName);
    while (readBytes < fileSize)
    {
        ReadFile(fp,buffer,this->_blockSize,&nRead,NULL);
        readBytes += nRead;
    }
    CloseHandle(fp);
}

#endif
