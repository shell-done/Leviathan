#include "training_supervisor.hpp"

TrainingSupervisor::TrainingSupervisor(int gridSize, int ppg) : m_ppg(ppg), m_gridSize(gridSize), m_mutationRate(10), m_generation(0), m_isLoading(false), m_nextGenReady(false), m_bestTrainingBox(nullptr) {
    
}

TrainingSupervisor::~TrainingSupervisor() {
    emptyTrainingBoxes();
}

int TrainingSupervisor::populationPerGeneration() {
    return m_ppg;
}

void TrainingSupervisor::setPopulationPerGeneration(int ppg) {
    m_ppg = ppg;
}

int TrainingSupervisor::gridSize() {
    return m_gridSize;
}

int TrainingSupervisor::mutationRate() {
    return m_mutationRate;
}

void TrainingSupervisor::setMutationRate(int rate) {
    m_mutationRate = rate;
}

int TrainingSupervisor::generation() {
    return m_generation;
}

int TrainingSupervisor::finished() {
    int finished = 0;

    for(int i=0; i<m_ppg; i++) {
        if(m_trainingBoxes[i]->isDead())
            finished++;
    }

    return finished;
}

bool TrainingSupervisor::isFinished() {
    for(int i=0; i<m_ppg; i++) {
        if(!m_trainingBoxes[i]->isDead())
            return false;
    }

    return true;
}

bool TrainingSupervisor::isLoading() {
    return m_isLoading;
}

void TrainingSupervisor::calculateFitnessSum() {
    m_fitnessSum = 0;

    for(int i=0; i<(int)m_trainingBoxes.size(); i++)
        m_fitnessSum += m_trainingBoxes[i]->fitnessScore();
}

double TrainingSupervisor::fitnessSum() {
    return m_fitnessSum;
}

Game* TrainingSupervisor::game(int tb) {
    return m_trainingBoxes[tb]->game();
}

NeuralNetwork* TrainingSupervisor::neuralNetwork(int tb) {
    return m_trainingBoxes[tb]->neuralNetwork();
}

void TrainingSupervisor::emptyTrainingBoxes() {
    for(int i=0; i<(int)m_trainingBoxes.size(); i++) {
        delete m_trainingBoxes[i];
    }

    m_trainingBoxes.clear();
}

void TrainingSupervisor::generateGeneration() {
    m_isLoading = true;
    std::vector<TrainingBox*> m_newGeneration;

    for(int i=0; i<m_ppg; i++) {
        TrainingBox* tb = new TrainingBox(m_gridSize);

        if(m_bestTrainingBox) {
            TrainingBox* parent1 = selectParent();
            TrainingBox* parent2 = selectParent();

            for(int j=0; j<tb->nbOfLayer(); j++) {
                Vector bias = parent1->layer(j)->bias;
                Matrix weights = parent1->layer(j)->weights;

                if(i == 0) {
                    bias = m_trainingBoxes[0]->layer(j)->bias;
                    weights = m_trainingBoxes[0]->layer(j)->weights;
                } else {
                    int randV = rand()%bias.dim();
                    std::default_random_engine generator;
                    std::normal_distribution<float> distribution(0.0, 1.0);

                    for(int v=0; v<bias.dim(); v++) {
                        if(v <= randV)
                            bias[v] = parent2->layer(j)->bias[v];

                        if(rand()%100 <= m_mutationRate) {
                            bias[v] += distribution(generator)/5;
                        }

                        if(bias[v] > 1) bias[v] = 1;
                        if(bias[v] < -1) bias[v] = -1;
                    }

                    int randM = rand()%weights.m();
                    int randN = rand()%weights.n();

                    for(int m=0; m<weights.m(); m++) {
                        for(int n=0; n<weights.n(); n++) {
                            if(m <= randM || (m == randM && n <= randN))
                                weights.setEl(m, n, parent2->layer(j)->weights.el(m, n));

                            if(rand()%100 <= m_mutationRate)
                                weights.setEl(m, n, weights.el(m, n) + distribution(generator)/2);

                            if(weights.el(m, n) > 1) weights.setEl(m, n, 1);
                            if(weights.el(m, n) < -1) weights.setEl(m, n, -1);
                        }
                    }
                }

                tb->setLayerBias(j, bias);
                tb->setLayerWeight(j, weights);
            }
        }

        m_newGeneration.push_back(tb);
    }

    emptyTrainingBoxes();
    m_bestTrainingBox = nullptr;
    m_trainingBoxes = m_newGeneration;
}

void TrainingSupervisor::runOneStep() {
    for(int i=0; i<(int)m_trainingBoxes.size(); i++)
        m_trainingBoxes[i]->runOne();
}

void TrainingSupervisor::runOneGeneration() {
    while(!isFinished()) {
        runOneStep();
    }
}

void TrainingSupervisor::selectBest() {
    calculateFitnessSum();

    sort(m_trainingBoxes.begin(), m_trainingBoxes.end(), [](TrainingBox* a, TrainingBox* b) {
        return a->fitnessScore() > b->fitnessScore();
    });
    
    m_generation++;
    std::cout << "Sum of Fitness scores for generation " << m_generation << " : " << m_fitnessSum << std::endl;
    std::cout << "Best score for generation " << m_generation << " : " << m_trainingBoxes.front()->fitnessScore() << std::endl;
    std::cout << "Worst score for generation " << m_generation << " : " << m_trainingBoxes.back()->fitnessScore() << std::endl;
    std::cout << std::endl;

    TrainingStats* ts = new TrainingStats(m_trainingBoxes);
    m_trainingStats.push_back(ts);

    m_isLoading = false;
    m_nextGenReady = true;
    m_bestTrainingBox = m_trainingBoxes[0];
    m_bestTrainingBox->replay();
}

TrainingBox* TrainingSupervisor::selectParent() {
    ulong r = ((((ulong)rand()) << 32) + rand())%ulong(m_fitnessSum);
    double sum = 0;

    for(int i=0; i<(int)m_trainingBoxes.size(); i++) {
        sum += m_trainingBoxes[i]->fitnessScore();

        if(sum > r)
            return m_trainingBoxes[i];
    }

    return m_trainingBoxes[0];
}

TrainingBox* TrainingSupervisor::bestTrainingBox() {
    return m_bestTrainingBox;
}

std::vector<TrainingStats*> TrainingSupervisor::trainingStats() {
    return m_trainingStats;
}

bool TrainingSupervisor::nextGenReady() {
    if(m_nextGenReady) {
        m_nextGenReady = false;
        return true;
    }

    return false;
}