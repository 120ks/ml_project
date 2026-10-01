#ifndef SELF_ATTENTION_LAYER_H
#define SELF_ATTENTION_LAYER_H
#include"matrix.h"

class Self_attention
{
    private:
        
        size_t dims{};
        //matrices K,V,Q
        Matrix key{dims, dims};
        Matrix value{dims, dims};
        Matrix query{dims, dims};
        const int layer_id{id_count};
    public:
        Self_attention(const size_t dimensions) : dims{dimensions}
        {id_count++;}
        Self_attention(const Self_attention &other)
        : Self_attention(other.dims)
        {
        }
        


        ~Self_attention();

        
    private:
        inline static int id_count{0};
};



#endif
