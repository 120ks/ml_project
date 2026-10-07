#include"matrix.h"
#include "math_constants.h"
#include <cmath>


Matrix get_transposed(const Matrix mx){
    Matrix transposed{mx.cols, mx.rows};
    for(size_t c{} ; c<mx.cols; c++){
        for(size_t r{} ; r<mx.rows ; r++){
            transposed(c, r)= mx(r, c);
        }
    }
    return transposed;
}

void Matrix::transpose()
{
    std::swap(rows, cols);
}

void Matrix::softmax(){
    this->for_each(math_const::E, Operation::raise_to);
    Matrix row_sums{Matrix_iterator<Matrix>::row_sums(*this)};
    this->col_wise(row_sums, Operation::divide);
}

Matrix softmax_derivative(const Matrix &mx, const Matrix &dmx)
{
    Matrix r_sums = Matrix_iterator<Matrix>::row_sums(mx * dmx);
    return mx * Matrix_iterator<Matrix>::col_wise(dmx, r_sums, Operation::substract);
}   

