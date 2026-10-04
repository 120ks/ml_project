#include "feed_forward.h"


Feed_forward::Feed_forward(const size_t dimensions)
: dims{dimensions}
{
    id_count++;
}

void Feed_forward::forward_propagate(Matrix &input)
{
    input_matrix = input;
    input = input*expansion;
    output_expand = input;
    for(size_t r{} ; r<input.rows ; r++){
        for(size_t c{} ; c<input.cols ; c++){
            if(input(r, c) < 0){
                act_derivative(r, c) = 0.01;
                input(r, c) *= 0.01;
            }
            else{act_derivative(r, c)  = 1;}
        }
    }
}

void Feed_forward::back_propagate(Matrix &loss) //loss exists outside the function
{
    //contract
    contraction_g = loss*output_expand;
    //pass further
    loss *= transpose(contraction);
    loss = direct_multiplication(loss, act_derivative);
    //expansion
    expansion_g = input_matrix * loss;
    loss *= transpose(expansion);
}


