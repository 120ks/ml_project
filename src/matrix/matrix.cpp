#include"matrix.h"
#include "matrix_iterator.h"
//constructors
Matrix::Matrix(const size_t row_count, const size_t col_count)
: Matrix_iterator{row_count, col_count}
{
    
}

Matrix::Matrix(const Matrix &other)
: Matrix(other.rows, other.cols)
{
    for(size_t r{0} ; r < other.rows ; r++){
        for(size_t c{0} ; c < other.cols ;  c++)
        {
            matrix[r*cols + c] = other.matrix[r*cols + c];
        }
    }
}
Matrix::Matrix(Matrix &&other) noexcept
: Matrix_iterator(std::move(other))
{

}



