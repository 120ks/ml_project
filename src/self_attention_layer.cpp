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
, kwq_weights{other.kwq_weights}
, kwq_grads{other.kwq_grads}
, kwq_out{other.kwq_out}
{
    id_count++;
}

Self_attention::Self_attention(Self_attention &&other)noexcept
: dims{other.dims}
, kwq_weights{std::move(other.kwq_weights)}
, kwq_grads{std::move(other.kwq_grads)}
, kwq_out{std::move(other.kwq_out)}
, layer_id{other.layer_id}
{}

void Self_attention::scaled_dot_product(Matrix &input)
{
    Matrix k{input*kwq_weights[key]};
    Matrix v{input*kwq_weights[value]};
    Matrix q{input*kwq_weights[query]};

    input = q*transpose(k); 
    for(auto &val : input.matrix){
        val /= std::sqrt(dims);
    }
    //row_wise softmax
    for(size_t r{0} ; r< input.rows ; r++){
        double sum{0};
        for(size_t c{0} ; c<input.cols ; c++){
            input(r, c) = std::pow(math_const::E, input(r, c));
            sum += input(r, c);
        }
        for(size_t c{0} ; c<input.cols ; c++){
            input(r, c) /= sum;
        }
    }
    input *= v;
}




//friend

