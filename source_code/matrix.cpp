#include"matrix.h"

//constructors
Matrix::Matrix(const size_t row_count, const size_t col_count)
: rows{row_count}
, cols{col_count}
, matrix(row_count*col_count, 0)
{
    
}
Matrix::~Matrix() = default;
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



//getters
size_t Matrix::get_cols()const {return cols;}
size_t Matrix::get_rows()const {return rows;}

Matrix Matrix::transpose(){
    std::vector<double> transposed(cols*rows);
    for(size_t c{} ; c<cols; c++){
        for(size_t r{} ; r<rows ; r++){
            transposed[c*rows + r] = matrix[r*cols + c];
        }
    }
    std::swap(cols, rows);
    matrix = std::move(transposed);
}

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

