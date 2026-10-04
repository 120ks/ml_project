#ifndef MATRIX_H
#define MATRIX_H

#include<iostream>
#include<vector>


class Self_attention;
class Feed_forward;

class Matrix{
    
    private:
        size_t rows{};
        size_t cols{};  
        std::vector<double> matrix{};

    public:
        //constructors
        explicit Matrix(const size_t row_count, const size_t col_count);
        Matrix(Matrix const &other);
        Matrix(Matrix &&other)noexcept;
        ~Matrix() = default;


        double& operator()(const size_t row, const size_t col); //indexing
        double operator()(const size_t row, const size_t col)const; //indexing
        Matrix& operator=(Matrix other) noexcept;
        Matrix& operator*=(const Matrix &other);

        size_t get_cols()const;
        size_t get_rows()const;

    private:
        void initialize();

        friend Matrix direct_multiplication(const Matrix &first, const Matrix &second);
        friend Matrix transpose(const Matrix mx);
        
        friend Matrix operator*(const Matrix &m1, const Matrix &m2);
        friend void softmax(Matrix &mx);

        friend class Self_attention;
        friend class Feed_forward;
};

#endif
