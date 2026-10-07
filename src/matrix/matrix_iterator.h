
#ifndef MATRIX_ITERATOR_H
#define MATRIX_ITERATOR_H

#include"matrix_container.h"
#include <cassert>
#include <cmath>

enum class Operation
{
    multiply,
    divide, 
    add,
    substract,
    raise_to,
    root_for

};   

template<typename deriv>
class Matrix_iterator : public Matrix_container 
{  
    private:
        inline static double apply_operation(const double val1, const double val2, Operation op){
            switch(op)
            {
                case(Operation::multiply): return val1*val2;
                case(Operation::add): return val1+val2;
                case(Operation::substract): return val1-val2;
                case(Operation::raise_to): return std::pow(val1, val2);
                case(Operation::root_for): return std::pow(val1, 1/val2);
                case(Operation::divide):
                {
                    assert(val2 != 0);
                    return val1 / val2;
                }
            }
            return 0;
        }

    inline auto& operator()(const size_t row, const size_t col){
        return matrix[row * cols + col];
    }
    

    protected:
        explicit Matrix_iterator(const size_t row_count, const size_t col_count) 
        : Matrix_container{row_count, col_count}{}

        Matrix_iterator(const Matrix_iterator &other) : Matrix_container{other}{}
        Matrix_iterator(Matrix_iterator &&other) noexcept : Matrix_container{std::move(other)}{}
        ~Matrix_iterator() = default;

    public:
        inline static deriv sub_cols(const size_t c_first, const size_t c_second, const deriv &mx1);
        inline static deriv sub_rows(const size_t r_first, const size_t r_second, const deriv &mx1);
        inline static deriv dot(const deriv &mx1, const deriv &mx2, Operation op = Operation::multiply);
        inline static deriv col_wise(const deriv &mx1, const deriv &col_mx, Operation op);
        inline static deriv row_wise(const deriv &mx1, const deriv &row_mx, Operation op);
        inline static deriv element(const deriv &mx1, const deriv &mx2, Operation op);
        inline static deriv for_each(const deriv &mx1, double val, Operation op);
        inline static deriv row_sums(const deriv &mx1);
        inline static deriv concat_cols(); //ei vielä
        inline static deriv concat_rows(); //ei vielä

        inline void for_each(double val, Operation op);
        inline void element(const deriv &other, Operation op);
        inline void col_wise(const deriv &col_mx, Operation op);
        inline void row_wise(const deriv &row_mx, Operation op);
        inline void replace_cols(deriv &mx1, const deriv &sub_cols); //ei vielä
        inline void replace_rows(deriv &mx1, const deriv &sub_rows); //ei vielä
        
        
};      

template<typename deriv>
void Matrix_iterator<deriv>::col_wise(const deriv &col_mx, Operation op)
{
    assert(col_mx.rows == rows && col_mx.cols == 1);
    for(size_t r{} ; r < rows ; r++){
        for(size_t c{}; c < cols ; c++){
            (*this)(r, c) = apply_operation((*this)(r, c), col_mx(r, 0), op);
        }
    }
}

template<typename deriv>
void Matrix_iterator<deriv>::row_wise(const deriv &row_mx, Operation op)
{
    assert(row_mx.cols == cols && row_mx.cols == 1);
    for(size_t r{} ; r < rows ; r++){
        for(size_t c{}; c < cols ; c++){
            (*this)(r, c) = apply_operation((*this)(r, c), row_mx(0, c), op);
        }
    }
}

template<typename deriv>
deriv Matrix_iterator<deriv>::col_wise(const deriv &mx1, const deriv &col_mx, Operation op)
{
    auto mx3{mx1};
    mx3.col_wise(col_mx, op);
    return mx3;
}

template<typename deriv>
deriv Matrix_iterator<deriv>::row_wise(const deriv &mx1, const deriv &row_mx, Operation op)
{
    auto mx3{mx1};
    mx3.row_wise(row_mx, op);
    return mx3;
}

template<typename deriv>
deriv Matrix_iterator<deriv>::sub_cols(const size_t c_first, const size_t c_second, const deriv &mx1)
{   
    assert(c_first<c_second && c_second<mx1.cols);
    deriv mx3{mx1.rows, c_second-c_first};

    for(size_t r{} ; r<mx1.rows ; r++){
        size_t sub_col{};
        for(size_t c{c_first} ; c<c_second ; c++){
            mx3(r, sub_col) = mx1(r, c);
        }
        sub_col++;
    }
    return mx3;
}

template<typename deriv>
deriv Matrix_iterator<deriv>::sub_rows(const size_t r_first, const size_t r_second, const deriv &mx1)
{   
    assert(r_first<r_second && r_second<mx1.rows);
    deriv mx3{r_second-r_first, mx1.cols};

    for(size_t r{r_first} ; r<r_second ; r++){
        size_t sub_row{};
        for(size_t c{} ; c<mx1.cols ; c++){
            mx3(sub_row, c) = mx1(r, c);
        }
        sub_row++;
    }
    return mx3;
}

template<typename deriv>
void Matrix_iterator<deriv>::for_each(double val, Operation op){
    for(size_t r{} ; r<rows ; r++){
        for(size_t c{} ; c<cols ; c++){
            (*this)(r, c) = apply_operation((*this)(r, c), val, op);
        }
    }
}

template<typename deriv>
void Matrix_iterator<deriv>::element(const deriv &other, Operation op){
    assert(rows == other.rows && cols == other.cols);
    for(size_t r{} ; r<rows ; r++){
        for(size_t c{} ; c<cols ; c++){
            (*this)(r, c) = apply_operation((*this)(r, c), other(r, c), op);
        }
    }
}

template<typename deriv>
deriv Matrix_iterator<deriv>::for_each(const deriv &mx1, double val, Operation op)
{   
    deriv mx3{mx1};
    mx3.for_each(val, op);
    return mx3;
}

template<typename deriv>
deriv Matrix_iterator<deriv>::element(const deriv &mx1, const deriv &mx2, Operation op)
{
    assert(mx1.rows == mx2.rows && mx1.cols == mx2.cols);
    deriv mx3{mx1};
    mx3.element(mx2, op);
    return mx3;
}

template<typename deriv>
deriv Matrix_iterator<deriv>::dot(const deriv &mx1, const deriv &mx2, Operation op)
{
    assert(mx1.cols == mx2.rows);
    deriv mx3{mx1.rows, mx2.cols};

    for(size_t r{} ; r<mx1.rows ; r++){
        for(size_t c{} ; c<mx2.cols ; c++){
            double rc_val{};
            for(size_t k{} ; k <mx2.rows ; k++)
            {
                rc_val += apply_operation(mx1(r, k), mx2(k, c), op);
            }
            mx3(r, c) = rc_val;
        }
    }
    return mx3;
}

template<typename deriv>
deriv Matrix_iterator<deriv>::row_sums(const deriv &mx1)
{
    deriv mx3{mx1.rows, 1};
    for(size_t r{} ; r<mx1.rows ; r++){
        double rc_val{};
        for(size_t c{} ; c<mx1.cols ; c++){
            rc_val += mx1(r, c);
        }
        mx3(r, 0) = rc_val;
    }
    return mx3;
}

#endif

