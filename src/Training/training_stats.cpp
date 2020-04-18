#include "training_stats.hpp"

TrainingStats::TrainingStats(std::vector<TrainingBox*> ts) {
    m_minFitnessScore = ts[0]->game()->fitness();
    m_maxFitnessScore = ts[0]->game()->fitness();
    m_avgFitnessScore = 0;
    m_sdFitnessScore = 0;

    for(int i=0; i<(int)ts.size(); i++) {
        if(ts[i]->game()->fitness() > m_maxFitnessScore)
            m_maxFitnessScore = ts[i]->game()->fitness();

        if(ts[i]->game()->fitness() < m_minFitnessScore)
            m_minFitnessScore = ts[i]->game()->fitness();

        m_avgFitnessScore += ts[i]->game()->fitness();
    }

    m_avgFitnessScore /= ts.size();

    for(int i=0; i<(int)ts.size(); i++) {
        m_sdFitnessScore += std::pow(m_avgFitnessScore - ts[i]->game()->fitness(), 2);
    }

    m_sdFitnessScore /= ts.size();
    m_sdFitnessScore = std::sqrt(m_sdFitnessScore);
}

double TrainingStats::minFitnessScore() const {
    return m_minFitnessScore;
}

double TrainingStats::maxFitnessScore() const {
    return m_maxFitnessScore;
}

double TrainingStats::avgFitnessScore() const {
    return m_avgFitnessScore;
}

double TrainingStats::sdFitnessScore() const {
    return m_sdFitnessScore;
}

void TrainingStats::print() const {
    std::cout << "------------ Stats ------------" << std::endl;
    std::cout << "Worst fitness score : " << std::to_string(m_minFitnessScore) << std::endl;
    std::cout << "Best fitness score : " << std::to_string(m_maxFitnessScore) << std::endl;
    std::cout << "Avg of fitness scores : " << std::to_string(m_avgFitnessScore) << std::endl;
    std::cout << "Sd of fitness scores : " << std::to_string(m_sdFitnessScore) << std::endl;
    std::cout << "-------------------------------" << std::endl << std::endl;
}