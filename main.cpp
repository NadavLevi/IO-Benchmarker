#include <Reader.hpp>
#include <iostream>

int main() {
    Reader reader(10, 1, false);
    reader.readWithIfstream("..\\Examples\\file2.txt");
    std::cout << "Finished" << std::endl;
    reader.readWithFread("..\\Examples\\file2.txt");
    std::cout << "Finished" << std::endl;
    reader.readWithMmap("..\\Examples\\file2.txt", true);
    std::cout << "Finished" << std::endl;
    reader.readWithMmap("..\\Examples\\file2.txt", false);
    std::cout << "Finished" << std::endl;
    reader.readWithRead("..\\Examples\\file2.txt");
    std::cout << "Finished" << std::endl;
    reader.readWithReadFile("..\\Examples\\file2.txt");
    std::cout << "Finished" << std::endl;
    return 1;
}