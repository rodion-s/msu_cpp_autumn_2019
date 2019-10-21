#include <iostream>
#include <cstdlib>
#include <stdexcept>

using namespace std;

class LinearAllocator
{
    char *storage, *current;
    size_t storage_size;
public:
    LinearAllocator(size_t maxSize) : storage_size(maxSize) {
        storage = static_cast<char*>(malloc(maxSize));
        if (!storage) {
            throw bad_alloc();
        }
        current = storage;
    }
    char* alloc(size_t size) {
        if (current - storage + size <= storage_size) {
            current += size;
            return current;
        } else {
            return nullptr;
        }
    }
    void reset() {
        current = storage;
    }
    ~LinearAllocator() {
        free(storage);
    }
};

int main(int argc, char *argv[])
{
    try {
        int init_size = stol(argv[1]);
        LinearAllocator allocator(init_size);
        cout << "Init " << init_size << " bytes" << endl;
        for (int i = 2; i < argc; ++i) {
            if (string(argv[i]).rfind("alloc:") == 0) {
                size_t size = stol(string(argv[i]).substr(string("alloc:").size()));
                if (allocator.alloc(size)) {
                    cout << "Allocated " << size << " bytes" << endl;
                } else {
                    cout << "null" << endl;
                }
            } else if (string(argv[i]) == "reset") {
                allocator.reset();
                cout << "Reseted" << endl;
            }
        }
    } catch (bad_alloc &exc) {
        cout << exc.what() << endl;
    }
    return 0;
}