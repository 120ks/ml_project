#include"matrix.h"

//constructors
Matrix::Matrix(const size_t row_count, const size_t col_count)
: rows{row_count}
, cols{col_count}
, matrix(row_count*col_count, 0)
{}
Matrix::~Matrix() = default;


//operators
double& Matrix::operator()(const size_t row, const size_t col){
    return matrix[row*cols + col];
}

void Matrix::transponse(){

}

//getters
size_t Matrix::get_cols()const {return cols;}
size_t Matrix::get_rows()const {return rows;}

