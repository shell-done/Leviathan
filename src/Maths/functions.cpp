#include "functions.hpp"

float Functions::unit(float x) {
    return x;
}

void Functions::unit(Vector& v) {
    S_UNUSED(v);
}

float Functions::ReLU(float x) {
    if(x < 0)
        return 0;

    return x;
}

void Functions::ReLU(Vector& v) {
    for(int i=0; i<v.dim(); i++) {
        v[i] = ReLU(v[i]);
    }
}

float Functions::sigmoid(float x) {
    return 1/(1+std::exp(-x));
}

void Functions::sigmoid(Vector& v) {
    for(int i=0; i<v.dim(); i++) {
        v[i] = sigmoid(v[i]);
    }
}
