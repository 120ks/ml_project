#ifndef MATRIX_H
#define MATRIX_H

#include<iostream>
#include<vector>


class Neuron_layer;


class Matrix{
    
    private:
        size_t rows{};
        size_t cols{};  
        std::vector<double> matrix{};

    public:
        explicit Matrix(const size_t row_count, const size_t col_count);
        ~Matrix() = default;

        double& operator()(const size_t row, const size_t col); //indexing
        double operator()(const size_t row, const size_t col)const; //indexing
        

        size_t get_cols()const;
        size_t get_rows()const;

        void transpose();

    private:
        void initialize();

        friend class Self_attention;
        friend Matrix&& operator*(const Matrix &m1, const Matrix &m2);
};

#endif
