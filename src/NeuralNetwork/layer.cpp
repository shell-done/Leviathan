#include "layer.hpp"

Layer::Layer(int in, int out, bool randomInit, void (*callback)(Vector& v)) : weights(out, in), bias(out), m_inNeurons(in), m_outNeurons(out), m_processFunction(callback) {
    if(randomInit) {
        for(int i=0; i<weights.m(); i++)
            for(int j=0; j<weights.n(); j++)
                weights.setEl(i, j, (rand()%2000)/1000.0 - 1);

        for(int i=0; i<bias.dim(); i++)
            bias[i] = (rand()%2000)/1000.0 - 1;
    }
}

int Layer::inputNeurons() {
    return m_inNeurons;
}

int Layer::outputNeurons() {
    return m_outNeurons;
}

Vector Layer::process(Vector& input) {
    Vector res = weights*input + bias;
    m_processFunction(res);

    return res;
}