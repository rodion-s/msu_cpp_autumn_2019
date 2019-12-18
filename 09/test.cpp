#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main(const int argc, const char **argv) {
	std::ifstream file("out.bin", std::ios::binary);
	file.seekg (0, file.end);
	uint64_t len = file.tellg() / sizeof(uint64_t);
	file.seekg(0, file.beg);
	uint64_t* arr = new uint64_t [len + 1];
	file.read(reinterpret_cast<char*>(arr), len * sizeof(uint64_t));
	if (std::is_sorted(arr, arr + len)) {
		cout << "File sorted" << endl;
	} else {
		cout << "File not sorted" << endl;
	}
	delete[] arr;
	file.close();
	return 0;
}