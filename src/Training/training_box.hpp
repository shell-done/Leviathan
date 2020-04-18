/*
 * File: training_box.hpp
 * Project: Leviathan
 * Version: 0.1
 * File Created: 12/04/2020 19:19
 * Author: Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * -----
 * Last Modified: 18/04/2020 16:10
 * Modified By: Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * -----
 * Copyright (c) 2020 - Alexandre THOMAS
 */

#ifndef TRAINING_BOX_HPP
#define TRAINING_BOX_HPP

#include "../Maths/vector.hpp"
#include "../Maths/matrix.hpp"
#include "../NeuralNetwork/layer.hpp"
#include "../NeuralNetwork/neural_network.hpp"
#include "../Game/game.hpp"

class TrainingBox {
public:
    TrainingBox(int gridSize);

    bool isDead();
    double fitnessScore();
    void runOne();
    void replay();

    Game* game();
    NeuralNetwork* neuralNetwork();

    int nbOfLayer();
    Layer* layer(int layer);
    void setLayerBias(int layer, Vector& bias);
    void setLayerWeight(int layer, Matrix& weights);

private:
    Game* m_game;
    NeuralNetwork* m_NeuralNetwork;
};

#endif // TRAINING_BOX_HPP