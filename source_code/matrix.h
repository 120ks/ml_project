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
        Matrix& operator*=(const Matrix &other);

        size_t get_cols()const;
        size_t get_rows()const;

        friend class Neuron_layer;

        void normalize(double min, double max);
        void transponse();
};

#endif
