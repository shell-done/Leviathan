/*
 * File: Layer.hpp
 * Project: Leviathan
 * Version: 0.1
 * File Created: 11/04/2020 17:03
 * Author: Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * -----
 * Last Modified: 18/04/2020 16:10
 * Modified By: Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * -----
 * Copyright (c) 2020 - Alexandre THOMAS
 */

#ifndef LAYER_HPP
#define LAYER_HPP

#include "../Maths/functions.hpp"
#include "../Maths/vector.hpp"
#include "../Maths/matrix.hpp"

class Layer {
public:
    Layer(int inputNeurons, int outputNeurons, bool randomInit = true, void (*callback)(Vector& v) = &Functions::unit);

    int inputNeurons();
    int outputNeurons();
    Vector process(Vector& input);

    Matrix weights;
    Vector bias;

private:
    int m_inNeurons;
    int m_outNeurons;
    void (*m_processFunction)(Vector& v);
};

#endif // LAYER_HPP