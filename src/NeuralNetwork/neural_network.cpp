#include "neural_network.hpp"

NeuralNetwork::NeuralNetwork() : m_isInitialized(false) {

}

NeuralNetwork::~NeuralNetwork() {
    for(int i=0; i<(int)m_layers.size(); i++)
        delete m_layers[i];
}

bool NeuralNetwork::isInitialized() {
    return m_isInitialized;
}

int NeuralNetwork::nbOfLayers() {
    return m_layers.size();
}

Layer* NeuralNetwork::layer(int layer) {
    if(layer < 0 && layer >= (int)m_layers.size())
        throw NeuralNetworkException("Attempt to get an out of bound layer");

    return m_layers[layer];
}

void NeuralNetwork::addLayer(int in, int out, void (*callback)(Vector& v)) {
    if(m_isInitialized)
        throw NeuralNetworkException("Cannot add layers while the network is already completed");

    if(!m_layers.empty()) {
        int prevOut = m_layers.back()->outputNeurons();
        
        if(prevOut != in) {
            throw NeuralNetworkException("This new layer must have as many input neurons as the previous layer output");
        }
    }

    Layer* layer = new Layer(in, out, true, callback);
    m_layers.push_back(layer);
}

void NeuralNetwork::setLayerBias(int layer, Vector& b) {
    if(layer < 0 && layer >= (int)m_layers.size())
        throw NeuralNetworkException("Attempt to get an out of bound layer");

    m_layers[layer]->bias = b;
}

void NeuralNetwork::setLayerWeights(int layer, Matrix& w) {
    if(layer < 0 && layer >= (int)m_layers.size())
        throw NeuralNetworkException("Attempt to get an out of bound layer");

    m_layers[layer]->weights = w;
}

void NeuralNetwork::completeNetwork(const std::vector<std::string>& outputTags) {
    if(m_layers.empty())
        throw NeuralNetworkException("Cannot complete a Neural Network with 0 layers");

    if((int)outputTags.size() != m_layers.back()->outputNeurons())
        throw NeuralNetworkException("There must be as many tags as output neurons from the last layer");

    m_tags = outputTags;
    m_isInitialized = true;
}

std::string NeuralNetwork::process(Vector input) {
    if(!m_isInitialized)
        throw NeuralNetworkException("Neural Network must be initialized");

    for(int i=0; i<(int)m_layers.size(); i++) {
        input = m_layers[i]->process(input);
    }

    int maxIdx = 0;
    float maxVal = input[0];

    for(int i=1; i<input.dim(); i++) {
        if(input[i] > maxVal) {
            maxVal = input[i];
            maxIdx = i;
        }
    }

    return m_tags[maxIdx];
}

std::vector<Vector> NeuralNetwork::middleVectors(Vector input) {
    if(!m_isInitialized)
        throw NeuralNetworkException("Neural Network must be initialized");

    std::vector<Vector> list;
    list.push_back(input);

    for(int i=0; i<(int)m_layers.size(); i++) {
        input = m_layers[i]->process(input);

        if(i == (int)m_layers.size() - 1) {
            int maxIdx = 0;
            float maxVal = input[0];

            for(int i=1; i<input.dim(); i++) {
                if(input[i] > maxVal) {
                    maxVal = input[i];
                    maxIdx = i;
                }
            }

            for(int i=0; i<input.dim(); i++)
                input[i] = i == maxIdx ? 1 : 0;
        }

        list.push_back(input);
    }

    return list;
}