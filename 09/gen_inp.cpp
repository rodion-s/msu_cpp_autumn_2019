#include <iostream>
#include <fstream>

int main(const int argc, const char **argv) {
    std::ofstream file("in.bin", std::ios::binary);
    for (size_t i = 0; i < 5 * 1024 * 1024; ++i) {
        uint64_t number = rand();
        file.write(reinterpret_cast<const char*>(&number), sizeof(uint64_t));
    }
    file.close();
    return 0;
}