#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <thread>
#include <algorithm>
#include <exception>

using namespace std;

constexpr size_t BLOCK_SIZE = 1024 * 1016;

void work()
{
    uint64_t *buf = new uint64_t[BLOCK_SIZE];
    ifstream input("in.bin", ios::binary);
    size_t tmp_file_count = 0;

    vector<string> tmp_file_names;
    while (input) {
        input.read(reinterpret_cast<char *>(buf), BLOCK_SIZE * sizeof(uint64_t));
        size_t readed_size = input.gcount() / sizeof(uint64_t);
        if (readed_size > 0) {
            tmp_file_names.push_back(to_string(tmp_file_count++));
            tmp_file_names.push_back(to_string(tmp_file_count++));

            std::thread t1([buf, readed_size]() { 
                sort(buf, buf + (readed_size / 2)); 
            });
            std::thread t2([buf, readed_size]() {
                sort(buf + readed_size / 2 , buf + readed_size);
            });
            t1.join();
            t2.join();
            

            std::ofstream f1(tmp_file_names[tmp_file_count - 2], std::ios::binary);
            if (!f1) {
                throw std::ofstream::failure(tmp_file_names[tmp_file_count - 2]);
            }
            f1.write(reinterpret_cast<const char*>(buf), sizeof(uint64_t) * readed_size / 2);

            std::ofstream f2(tmp_file_names[tmp_file_count - 1], std::ios::binary);
            f2.write(reinterpret_cast<const char*>(buf + readed_size / 2), sizeof(uint64_t) * readed_size / 2);
            if (!f2) {
                throw std::ofstream::failure(tmp_file_names[tmp_file_count - 1]);
            }
            f1.close();
            f2.close();
        
        }
    }
    input.close();
    delete[] buf;
    ofstream out("out.bin", ios::binary);
    vector <ifstream> tmp_files (tmp_file_count);

   
    for (size_t i = 0; i < tmp_file_count; ++i) {
        tmp_files[i] = ifstream(tmp_file_names[i], ios::binary | ios::in);
        if (!tmp_files[i]) {
            throw std::ifstream::failure(tmp_file_names[i]);
        }
    }
   
    auto my_comparator = [](const pair<uint64_t, int>& lhs, const pair<uint64_t, int>& rhs) {
        return lhs.first > rhs.first;
    };
    priority_queue<pair<uint64_t, int>,
                   vector<pair<uint64_t, int>>,
                   decltype(my_comparator)> heap(my_comparator);

   
    for (size_t i = 0; i < tmp_file_count; ++i) {
        uint64_t number; // pair(current_number on file i, index of file i)
        tmp_files[i].read(reinterpret_cast<char *>(&number), sizeof(uint64_t));
        heap.emplace(make_pair(number, i));
    }

    while (!heap.empty()) {        
        uint64_t current = heap.top().first;
        size_t file_idx = heap.top().second;

        heap.pop();
        out.write(reinterpret_cast<char *>(&current), sizeof(uint64_t));
        
        if (tmp_files[file_idx].peek() != EOF) {
            uint64_t next;
            tmp_files[file_idx].read(reinterpret_cast<char*>(&next), sizeof(uint64_t));
            heap.emplace(make_pair(next, file_idx));
        }
    }
    for (size_t i = 0; i < tmp_file_count; ++i) {
        tmp_files[i].close();
        remove(tmp_file_names[i].c_str());
    }
    out.close();
}
int main(void)
{
    try {
        work();   
    } catch (std::exception &exc) {
        cout << exc.what() << endl;
        return 1;
    }
    cout << "Done" << endl;
    return 0;
}