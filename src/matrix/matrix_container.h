#ifndef MATRIX_CONTAINER_H
#define MATRIX_CONTAINER_H
#include<vector>


class Matrix_container
{
    protected:
        size_t rows{};
        size_t cols{};
        std::vector<double> matrix{};

        Matrix_container(const size_t row_count, const size_t col_count);
        Matrix_container(const Matrix_container &other);
        Matrix_container(Matrix_container &&other)noexcept;

};
#endif
