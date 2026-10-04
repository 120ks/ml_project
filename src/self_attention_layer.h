#ifndef SELF_ATTENTION_LAYER_H
#define SELF_ATTENTION_LAYER_H
#include"matrix.h"
#include <map>

class Self_attention
{       
    enum kwq
        {
            key,
            value,
            query
        };

    private:
        
        size_t dims{};
        const int layer_id{id_count};
        //matrices K,V,Q
        std::map<kwq, Matrix> kwq_weights{
            {kwq::key, Matrix{dims, dims}},
            {kwq::value, Matrix{dims, dims}},
            {kwq::query, Matrix{dims, dims}}};
        std::map<kwq, Matrix> kwq_grads {kwq_weights}; //grads
        std::map<kwq, Matrix> kwq_out{kwq_weights}; //output



        
    public:
        Self_attention(const size_t dimensions);
        Self_attention(const Self_attention &other);
        Self_attention(Self_attention &&other) noexcept;
        ~Self_attention();
        Self_attention operator=(Self_attention) = delete;

        void scaled_dot_product(Matrix &input);
        

    private:
        inline static int id_count{0};
};



#endif
