/*
 * File: NeuralNetwork.hpp
 * Project: Leviathan
 * Version: 0.1
 * File Created: 11/04/2020 01:00
 * Author: Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * -----
 * Last Modified: 18/04/2020 16:10
 * Modified By: Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * -----
 * Copyright (c) 2020 - Alexandre THOMAS
 */

#ifndef NEURAL_NETWORK_HPP
#define NEURAL_NETWORK_HPP

#include <vector>
#include "neural_network_exception.hpp"
#include "layer.hpp"

class NeuralNetwork {
public:
    NeuralNetwork();
    ~NeuralNetwork();
    bool isInitialized();

    int nbOfLayers();
    Layer* layer(int layer);
    void addLayer(int inputNeuron, int outputNeuron, void (*callback)(Vector& v) = &Functions::unit);
    void setLayerBias(int layer, Vector& bias);
    void setLayerWeights(int layer, Matrix& weights);

    void completeNetwork(const std::vector<std::string>& outputTags);
    std::string process(Vector input);
    std::vector<Vector> middleVectors(Vector input);

private:
    bool m_isInitialized;
    std::vector<Layer*> m_layers;
    std::vector<std::string> m_tags;
};

#endif // NEURAL_NETWORK_HPP