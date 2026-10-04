#ifndef FEED_FORWARD_H
#define FEED_FORWARD_H

#include "matrix.h"
#include <memory>

class Feed_forward
{
    private:

        size_t dims{};
        int layer_id{id_count};

        //input
        Matrix input_matrix{dims, dims};

        //weights
        Matrix expansion{dims, dims*4};
        Matrix contraction{dims*4, dims};
        //grads
        Matrix expansion_g{dims, dims*4};
        Matrix contraction_g{dims*4, dims};

        Matrix output_expand{dims, dims*4};
        //derivative
        Matrix act_derivative{dims, dims*4};

    public:
        Feed_forward(const size_t dimensions);
        ~Feed_forward() = default;

        Feed_forward(const Feed_forward &other) = delete;
        Feed_forward(const Feed_forward &&other) = delete;
        Feed_forward& operator=(Feed_forward other) = delete;

        void forward_propagate(Matrix &input);
        void back_propagate(Matrix &loss);
        
    private:
        inline static int id_count{0};

};


#endif
