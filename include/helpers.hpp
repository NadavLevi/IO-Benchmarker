#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <cstdint>
#include <string>
#include <filesystem>

static const uint64_t KB = 1024;
static const uint64_t MB = (1024*KB);
static const uint64_t GB = (1024*MB);

static const uint64_t FILE_SIZE = 1 * MB;
static const uint64_t BLOCK_SIZE = 1024;

static const uint8_t NUM_OF_JOBS = 1;

static std::string FILE_NAME = "";

uint64_t getFileSize(const std::string& fileName) {
    return std::filesystem::file_size(fileName);
}

#endif
