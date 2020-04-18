#include "core.hpp"
#include "Game/game.hpp"
#include "Graphics/view.hpp"
#include "Maths/vector.hpp"
#include "Maths/functions.hpp"
#include "NeuralNetwork/neural_network.hpp"
#include "Training/training_supervisor.hpp"

#include "Maths/matrix.hpp"
#include "Maths/vector.hpp"

int main(int argc, char** argv) {
    S_UNUSED(argc);
    S_UNUSED(argv);

    std::srand(std::time(nullptr));

    TrainingSupervisor supervisor(25, 4000);
    View view;

    for(int i=0; i<100; i++) {
        supervisor.generateGeneration();

        while(!supervisor.isFinished()) {
            supervisor.runOneStep();
            view.render(&supervisor);
        }

        supervisor.selectBest();
        TrainingBox* best = supervisor.bestTrainingBox();
        while(!best->game()->isDead()) {
            best->runOne();
            view.render(&supervisor);
        }
    }

    return EXIT_SUCCESS;
}