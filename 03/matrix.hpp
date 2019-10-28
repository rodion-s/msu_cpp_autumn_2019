
class Matrix
{
    const int rows, cols;
    int **storage;
    Matrix(const Matrix &other) = delete;
    Matrix& operator= (const Matrix &other) = delete;
public:
    class Proxy
    {
        int **storage;
        const int row_idx;
        const int cols;
    public:
        Proxy(int **addr, int row_idx, int cols) : storage(addr), row_idx(row_idx), cols(cols) {}
        int& operator[] (int col_idx) {
            if (col_idx >= cols) {
                throw std::out_of_range("");
            }
            return storage[row_idx][col_idx];
        } 
    };
    
    Matrix(int rows, int cols) : rows(rows), cols(cols) {
        storage = new int*[rows];
        for (int i = 0; i < rows; ++i) {
            storage[i] = new int[cols]();
        }
    }
    ~Matrix() {
        for (int i = 0; i < rows; ++i) {
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
    Proxy operator[] (int row_idx) {
        if (row_idx >= rows) {
            throw std::out_of_range("");
        }
        return Proxy(storage, row_idx, cols);
    }
    
    bool operator== (const Matrix &other) const {
        if (rows != other.rows || cols != other.cols) {
            return false;
        }
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
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
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                storage[i][j] *= value;
            }
        }
        return *this;
    }
};