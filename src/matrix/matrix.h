#ifndef MATRIX_H
#define MATRIX_H


#include "matrix_iterator.h"

class Feed_forward;

class Matrix : public Matrix_iterator<Matrix>
{   
    bool is_transposed{false};

    public:
        //constructors
        explicit Matrix(const size_t row_count = 0, const size_t col_count = 0);
        Matrix(Matrix const &other);
        Matrix(Matrix &&other)noexcept;
        ~Matrix() = default;

        //operator member
        double& operator()(const size_t row, const size_t col); //indexing
        double operator()(const size_t row, const size_t col)const; //indexing

        Matrix& operator=(Matrix other) noexcept;

        Matrix& operator*=(const Matrix &other);
        Matrix& operator+=(const Matrix &other);
        Matrix& operator-=(const Matrix &other);
        Matrix& operator/=(const Matrix &other);

        void transpose();
        void softmax();
        

    private:
        
        //operator friend
        friend Matrix operator*(const Matrix &mx1, const Matrix &mx2);
        friend Matrix operator+(const Matrix &mx1, const Matrix &mx2);
        friend Matrix operator-(const Matrix &mx1, const Matrix &mx2);
        friend Matrix operator/(const Matrix &mx1, const Matrix &mx2);
        //friend functions
        friend Matrix get_transposed(const Matrix mx1);
        friend Matrix softmax_derivative(const Matrix &mx, const Matrix &dAmx);

        friend class Feed_forward;
};

#endif
