#include "training_box.hpp"

TrainingBox::TrainingBox(int gridSize) {
    m_game = new Game(gridSize);
    m_NeuralNetwork = new NeuralNetwork();

    m_NeuralNetwork->addLayer(24, 18, Functions::ReLU);
    m_NeuralNetwork->addLayer(18, 18, Functions::ReLU);
    m_NeuralNetwork->addLayer(18, 4, Functions::ReLU);
    m_NeuralNetwork->completeNetwork(std::vector<std::string>{"Z", "D", "S", "Q"});
}

bool TrainingBox::isDead() {
    return m_game->isDead();
}

double TrainingBox::fitnessScore() {
    return m_game->fitness();
}

void TrainingBox::runOne() {
    std::string dir = m_NeuralNetwork->process(m_game->inputVector());
    
    m_game->move((Game::Direction)(dir[0]));
}

void TrainingBox::replay() {
    std::vector<Vector2D> fruitsPos = m_game->fruitsPos();
    int gridSize = m_game->gridSize();

    delete m_game;

    m_game = new Game(gridSize, fruitsPos);
}

Game* TrainingBox::game() {
    return m_game;
}

NeuralNetwork* TrainingBox::neuralNetwork() {
    return m_NeuralNetwork;
}

int TrainingBox::nbOfLayer() {
    return m_NeuralNetwork->nbOfLayers();
}

Layer* TrainingBox::layer(int layer) {
    return m_NeuralNetwork->layer(layer);
}

void TrainingBox::setLayerBias(int layer, Vector& b) {
    m_NeuralNetwork->setLayerBias(layer, b);
}

void TrainingBox::setLayerWeight(int layer, Matrix& w) {
    m_NeuralNetwork->setLayerWeights(layer, w);
}