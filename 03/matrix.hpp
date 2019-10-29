
class Matrix
{
    size_t rows, cols;
    int **storage;
    Matrix(const Matrix &other) = delete;
    Matrix& operator= (const Matrix &other) = delete;
public:
    class Proxy
    {
        int **storage;
        size_t row_idx;
        size_t cols;
    public:
        Proxy(int **addr, size_t row_idx, size_t cols) : storage(addr), row_idx(row_idx), cols(cols) {}
        int& operator[] (size_t col_idx) {
            if (col_idx >= cols) {
                throw std::out_of_range("");
            }
            return storage[row_idx][col_idx];
        } 
    };
    
    Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
        storage = new int*[rows];
        for (size_t i = 0; i < rows; ++i) {
            storage[i] = new int[cols]();
        }
    }
    ~Matrix() {
        for (size_t i = 0; i < rows; ++i) {
            delete[] storage[i];
        }
        delete[] storage;
    }
    int getRows() const {
        return rows;
    }
    int getColumns() const {
        return cols;
    }
    Proxy operator[] (size_t row_idx) const {
        if (row_idx >= rows) {
            throw std::out_of_range("");
        }
        return Proxy(storage, row_idx, cols);
    }
    
    bool operator== (const Matrix &other) const {
        if (rows != other.rows || cols != other.cols) {
            return false;
        }
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                if (storage[i][j] != other.storage[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
    bool operator!= (const Matrix &other) const {
        return !(*this == other);
    }

    Matrix& operator*= (int value) {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                storage[i][j] *= value;
            }
        }
        return *this;
    }
};