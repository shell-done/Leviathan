/*
 * File: training_stats.hpp
 * Project: Leviathan
 * Version: 0.1
 * File Created: 16/04/2020 18:12
 * Author: Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * -----
 * Last Modified: 18/04/2020 16:10
 * Modified By: Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * -----
 * Copyright (c) 2020 - Alexandre THOMAS
 */

#ifndef TRAINING_STATS
#define TRAINING_STATS

#include <iostream>
#include <cmath>
#include "training_box.hpp"

class TrainingStats {
public:
    TrainingStats(std::vector<TrainingBox*> trainingBoxes);

    double minFitnessScore() const;
    double maxFitnessScore() const;
    double avgFitnessScore() const;
    double sdFitnessScore() const;

    void print() const;

private:
    int m_generation;
    double m_minFitnessScore;
    double m_maxFitnessScore;
    double m_avgFitnessScore;
    double m_sdFitnessScore;
};

#endif // TRAINING_STATS