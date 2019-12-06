#include <iostream>
#include "threadpool.h"

using namespace std;
int main() {
    ThreadPool pool(8);

    for (int i = 0; i < 100; ++i) {
        cout<<pool.exec([i]() { return i; }).get() << endl;
    }
}

