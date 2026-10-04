#include"matrix.h"
#include <cassert>
//constructors
Matrix::Matrix(const size_t row_count, const size_t col_count)
: rows{row_count}
, cols{col_count}
, matrix(row_count*col_count, 0)
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
: rows{other.rows}
, cols{other.cols}
, matrix{std::move(other.matrix)}
{

}

//operators
double& Matrix::operator()(const size_t row, const size_t col){
    return matrix[row*cols + col];
}
double Matrix::operator()(const size_t row, const size_t col)const {
    return matrix[row*cols + col];
}
Matrix& Matrix::operator=(Matrix other)noexcept
{
    if(this == &other){
        return *this;
    }
    std::swap(matrix, other.matrix);
    rows = other.rows;
    cols = other.cols;
    return *this;
}

Matrix& Matrix::operator*=(const Matrix &other){
    assert(cols == other.rows && "dimension mismatch");
    *this = (*this) * other; 
}



//getters
size_t Matrix::get_cols()const {return cols;}
size_t Matrix::get_rows()const {return rows;}





//friend funktions

Matrix operator*(const Matrix &m1, const Matrix &m2){
    if(m1.rows != m2.cols){
        throw("matrix_multiplication_row1!=col2");
    }
    Matrix m3(m1.rows, m2.cols);
    for(size_t r1{} ; r1 < m1.rows ; r1++){
        for(size_t c2 ; c2 <m2.cols ; c2++){
            double sum{0};
            for(size_t r2{} ; r2<m2.rows ; r2++){
                sum += m1(r1, r2) * m2(r2, c2);
            }
        m3(r1, c2) = sum;
        }
    }
    return m3;
}

Matrix transpose(const Matrix mx){
    Matrix transposed{mx.cols, mx.rows};
    for(size_t c{} ; c<mx.cols; c++){
        for(size_t r{} ; r<mx.rows ; r++){
            transposed(c, r)= mx(r, c);
        }
    }
    return transposed;

}Matrix direct_multiplication(const Matrix &first, const Matrix &second){
    assert(first.rows == second.rows && "row mismatch"); //debug
    assert(first.cols == second.cols && "col mismatch"); //debug
    
    Matrix third{first.rows, second.rows};
    for(size_t r{0} ; r<first.rows; r++){
        for(size_t c{0} ; c<first.cols; c++){
            third(r, c) = first(r, c)*second(r, c);
        }
    }
    return third;
}
