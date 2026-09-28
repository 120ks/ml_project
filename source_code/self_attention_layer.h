#ifndef SELF_ATTENTION_LAYER_H
#define SELF_ATTENTION_LAYER_H
#include"matrix.h"

class Self_attention
{
    private:
        //matrices K,V,Q
        Matrix key;
        Matrix value;
        Matrix query;
        int layer_id{};
    public:
        Self_attention();
        ~Self_attention();
        
    private:
        inline static int id_count{0};
};



#endif
