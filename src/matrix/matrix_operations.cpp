
#include"matrix.h"
//operators
double& Matrix::operator()(const size_t row, const size_t col)
{
    assert((row<rows && 0<= row) &&(col<cols && 0<= col));
    return matrix[row*cols + col];
}
double Matrix::operator()(const size_t row, const size_t col)const
{
    assert((row<rows && 0<= row) &&(col<cols && 0<= col));
    return matrix[row*cols + col];
}
Matrix& Matrix::operator=(Matrix other)noexcept
{
    if(this == &other){return *this;}
    
    std::swap(matrix, other.matrix);
    rows = other.rows;
    cols = other.cols;
    return *this;
}

Matrix& Matrix::operator/=(const Matrix &other)
{
    this->element(other, Operation::divide);
    return *this;
}

Matrix operator/(const Matrix &mx1, const Matrix &mx2)
{
    return Matrix_iterator<Matrix>::element(mx1, mx2, Operation::divide);
}

Matrix& Matrix::operator*=(const Matrix &other)
{
    this->element(other, Operation::multiply);
    return *this;
}

Matrix operator*(const Matrix &mx1, const Matrix &mx2)
{
    return Matrix_iterator<Matrix>::element(mx1, mx2, Operation::multiply);
}

Matrix& Matrix::operator+=(const Matrix &other)
{
    this->element(other, Operation::add);
    return *this;
}

Matrix operator+(const Matrix &mx1, const Matrix &mx2)
{
    return Matrix_iterator<Matrix>::element(mx1, mx2, Operation::add);
}

Matrix& Matrix::operator-=(const Matrix &other)
{
    this->element(other, Operation::substract);
    return *this;
}

Matrix operator-(const Matrix &mx1, const Matrix &mx2)
{
    return Matrix_iterator<Matrix>::element(mx1, mx2, Operation::substract);
}


