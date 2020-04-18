/*
 * File: training_supervisor.hpp
 * Project: Leviathan
 * Version: 0.1
 * File Created: 12/04/2020 19:35
 * Author: Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * -----
 * Last Modified: 18/04/2020 16:10
 * Modified By: Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * -----
 * Copyright (c) 2020 - Alexandre THOMAS
 */

#ifndef TRAINING_SUPERVISOR_HPP
#define TRAINING_SUPERVISOR_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "training_box.hpp"
#include "training_stats.hpp"

class TrainingSupervisor {
public:
    TrainingSupervisor(int gridSize, int populationPerGeneration);
    ~TrainingSupervisor();

    int populationPerGeneration();
    void setPopulationPerGeneration(int populationPerGeneration);
    int gridSize();
    int mutationRate();
    void setMutationRate(int mutationRate);
    int generation();
    int finished();
    bool isFinished();
    bool isLoading();
    void calculateFitnessSum();
    double fitnessSum();
    Game* game(int trainingBox);
    NeuralNetwork* neuralNetwork(int trainingBox);

    void emptyTrainingBoxes();

    void generateGeneration();
    void runOneStep();
    void runOneGeneration();
    void selectBest();
    TrainingBox* selectParent();
    TrainingBox* bestTrainingBox();
    std::vector<TrainingStats*> trainingStats();
    bool nextGenReady();

private:
    int m_ppg;
    int m_gridSize;
    int m_mutationRate;
    int m_generation;
    bool m_isLoading;
    double m_fitnessSum;
    bool m_nextGenReady;
    std::vector<TrainingBox*> m_trainingBoxes;
    TrainingBox* m_bestTrainingBox;
    std::vector<TrainingStats*> m_trainingStats;
};

#endif // TRAINING_SUPERVISOR_HPP