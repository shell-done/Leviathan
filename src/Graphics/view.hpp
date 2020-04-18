/*
 * File: view.hpp
 * Project: Leviathan
 * Version: 0.1
 * File Created: 09/04/2020 01:58
 * Author: Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * -----
 * Last Modified: 18/04/2020 16:10
 * Modified By: Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * -----
 * Copyright (c) 2020 - Alexandre THOMAS
 */

#ifndef VIEW_HPP
#define VIEW_HPP

#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "graphic_exception.hpp"
#include "../Game/board.hpp"
#include "../Game/game.hpp"
#include "../NeuralNetwork/neural_network.hpp"
#include "../Training/training_supervisor.hpp"
#include "../Training/training_stats.hpp"

class View {
public:
    View();

    void drawGame(TrainingSupervisor* trainingSupervisor);
    void drawLoading(TrainingSupervisor* trainingSupervisor);
    void drawStats(TrainingSupervisor* trainingSupervisor);
    void drawReplay(TrainingSupervisor* trainingSupervisor);
    void drawNeuralNetwork(TrainingSupervisor* trainingSupervisor);
    void render(TrainingSupervisor* trainingSupervisor);
    bool isOpen();

private:
    sf::RenderWindow* m_window;
    sf::Texture m_gameTileset;
    sf::Texture m_nodeTileset;
    sf::Font m_font;
    std::map<Board::Tile, sf::IntRect> m_tileRects;
    int m_currentGen = 1;

    void loadResources();
    int tileRotation(Game::Direction direction);
    void drawSprite(Board::Tile tile, int x, int y, int r = 0);
    void drawSprite(Board::Tile tile, sf::Vector2i pos, int r = 0);
};

#endif // VIEW_HPP