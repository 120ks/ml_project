#include "matrix_container.h"
#include <functional>

Matrix_container::Matrix_container(const size_t row_count, const size_t col_count)
: rows{row_count}
, cols{col_count}
, matrix(row_count*col_count, 0)
{
    
}

Matrix_container::Matrix_container(const Matrix_container &other)
: Matrix_container(other.rows, other.cols)
{
    for(size_t r{0} ; r < other.rows ; r++){
        for(size_t c{0} ; c < other.cols ;  c++)
        {
            matrix[r*cols + c] = other.matrix[r*cols + c];
        }
    }
}

Matrix_container::Matrix_container(Matrix_container &&other) noexcept
: rows{other.rows}
, cols{other.cols}
, matrix{std::move(other.matrix)}
{}
