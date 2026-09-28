#ifndef MATRIX_H
#define MATRIX_H

#include<vector>

class Neuron_layer;

class Matrix{
    private:
        size_t rows{};
        size_t cols{};  
        std::vector<double> matrix{};

    public:
        explicit Matrix(const size_t row_count, const size_t col_count);
        double& operator()(const size_t row, const size_t col);
        Matrix& operator*=(const Matrix &other);

        size_t get_cols()const {return cols;}
        size_t get_rows()const {return rows;}

        friend class Neuron_layer;


};

#endif
