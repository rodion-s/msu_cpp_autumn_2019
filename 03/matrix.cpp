#include <iostream>
#include <stdexcept>
#include <cassert>
#include "matrix.hpp"

using namespace std;
int main(int argc, char *argv[])
{
    if (argc < 2) {
        return 0;
    }
    const size_t rows = 5;
    const size_t cols = 3;
    Matrix m(rows, cols);
    Matrix m1(rows, cols);
    Matrix m2(rows, cols);
    const Matrix cm(rows, cols);
    const Matrix cm1(rows, cols);
    const Matrix cm2(rows, cols);
    Matrix testm(0, 0);
    switch (stoi(argv[1])) {

        case 1:
            assert(m.getRows() == 5);
            assert(m.getColumns() == 3);
            break;
        case 2:
            assert(cm.getRows() == 5);
            assert(cm.getColumns() == 3);
            break;
        case 3:
            assert(m == m);
            break;
        case 4:
            assert(m1 == m2);
            break;
        case 5:
            assert(!(m1 != m2));
            break;
        case 6:
            assert(cm1 == cm2);
            break;
        case 7:
            assert(!(cm1 != cm2));
            break;
        case 8:
            m[0][0] = 1;
            m[0][1] = 2;
            m[1][0] = 3;
            m[1][1] = 4;
            assert(m[0][0] == 1 && m[0][1] == 2 && m[1][0] == 3 && m[1][1] == 4);
            break;
        case 9:
            m[0][0] = 1;
            m[0][1] = 2;
            m[1][0] = 3;
            m[1][1] = 4;
            m *= 3;
            assert(m[0][0] == 3 && m[0][1] == 6 && m[1][0] == 9 && m[1][1] == 12);
            break;
        case 10:
            {
                m[4][2] = 5;
                double x = m[4][2];
                assert(x == 5);
            }
                break;
        case 11:
            {
                m[4][2] = 5;
                double x = m[4][2];
                x = 6;
                assert(x == 6 && m[4][2] == 5);
            }
                break;
        case 12:
            assert(cm[0][2] == 0);
            break;
        case 13:
            try {
                m[5][3];
            } catch (out_of_range &exc) {
                cout << "out of range" << endl;
            }
            break;
        case 14:
            try {
                m[4][3];
            } catch (out_of_range &exc) {
                cout << "out of range" << endl;
            }
            break;
        case 15:
            try {
                testm[0][0];
            } catch (out_of_range &exc) {
                cout << "out of range" << endl;
            }
            break;
        default:
            cout << "There is no test " << stoi(argv[1]) << endl;
            return 0;
    }
    cout << "OK" << endl;

    return 0;
}