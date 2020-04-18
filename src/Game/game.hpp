/*
 * File: game.hpp
 * Project: Leviathan
 * Version: 0.1
 * File Created: 07/04/2020 19:29
 * Author: Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * -----
 * Last Modified: 18/04/2020 16:10
 * Modified By: Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * -----
 * Copyright (c) 2020 - Alexandre THOMAS
 */

#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <queue>
#include <cmath>

#include "board.hpp"
#include "../Maths/vector.hpp"
#include "../Maths/vector2d.hpp"

class Game {
public:
    enum class Direction {
        UP = 'Z', RIGHT = 'D', DOWN = 'S', LEFT = 'Q'
    };

    Game(int gridSize, std::vector<Vector2D> replayFruits = std::vector<Vector2D>());
    int gridSize();
    Board::Tile** grid();

    int score();
    int moves();
    int movesLeft();
    double fitness();
    Direction headDirection();
    bool isDead();

    Vector2D snakeHead();
    Vector2D fruit();

    void move(Direction direction);
    void generateFruit();
    Vector inputVector();
    std::vector<Vector2D> fruitsPos();
    
    void print();

private:
    Board m_board;
    int m_score;
    int m_moves;
    int m_movesLeft;
    Direction m_headDirection;
    Vector2D m_fruit;
    bool m_isDead;
    bool m_isReplay;

    std::queue<Vector2D> m_snake;
    std::vector<Vector2D> m_fruitPos;

    float distThreshold(int dist);
};

#endif // GAME_HPP