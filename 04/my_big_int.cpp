#include <iostream>
#include <cstring>
#include "my_big_int.hpp"
#include <climits>
using namespace std;
int main()
{
	BigInt a(LLONG_MAX);
	BigInt b(12345678);
	cout << a + b << endl;
	return 0;
}
