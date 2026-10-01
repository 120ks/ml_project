#include "self_attention_layer.h"
#include <cmath>
#include "math_constants.h"
//constructors

Self_attention::Self_attention(const size_t dimensions) : dims{dimensions}
{
    id_count++;
}

Self_attention::Self_attention(const Self_attention &other)
: dims{other.dims}
, key_w{other.key_w}
, value_w{other.value_w}
, query_w{other.query_w}
, key_grad{other.key_grad}
, value_grad{other.value_grad}
, query_grad{other.query_grad}
, output_matrix{other.output_matrix}
{
    id_count++;
}

Self_attention::Self_attention(Self_attention &&other)
: dims{other.dims}
, key_w{std::move(other.key_w)}
, value_w{std::move(other.value_w)}
, query_w{std::move(other.query_w)}
, key_grad{std::move(other.key_grad)}
, value_grad{std::move(other.value_grad)}
, query_grad{std::move(other.query_grad)}
, output_matrix{std::move(other.output_matrix)}
, layer_id{other.layer_id}
{}

Matrix Self_attention::scaled_dot_product(const Matrix &input)
{
    Matrix k{ std::move(input*key_w) };
    Matrix v{ std::move(input*value_w) };
    Matrix q{ std::move(input*query_w) };

    k.transpose();

    Matrix dotProduct{std::move(v*k)};
    for(auto &val : dotProduct.matrix){
        val /= std::sqrt(dims);
    }
    softmax(dotProduct);
    output_matrix = dotProduct*v;
    return dotProduct*v;
    
}


//friend
void softmax(Matrix &mx){
    for(auto val : mx.matrix){
        val = std::pow(math_const::E, val);
    }
}
