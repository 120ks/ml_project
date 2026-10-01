#ifndef SELF_ATTENTION_LAYER_H
#define SELF_ATTENTION_LAYER_H
#include"matrix.h"


class Self_attention
{
    private:
        
        size_t dims{};
        //matrices K,V,Q
        Matrix key_w{dims, dims};
        Matrix value_w{dims, dims};
        Matrix query_w{dims, dims};
        //grads k,v,q
        Matrix key_grad{dims, dims};
        Matrix value_grad{dims, dims};
        Matrix query_grad{dims, dims};

        Matrix output_matrix{dims, dims};

        const int layer_id{id_count};
    public:
        Self_attention(const size_t dimensions);
        Self_attention(const Self_attention &other);
        Self_attention(Self_attention &&other) noexcept;
        ~Self_attention();
        Self_attention operator=(Self_attention) = delete;

        Matrix scaled_dot_product(const Matrix &input);
        Matrix grad_output(const Matrix &gradiant);

    private:
        inline static int id_count{0};
        friend void softmax(Matrix &mx);
};



#endif
