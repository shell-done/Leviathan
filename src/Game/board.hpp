/*
 * File: board.hpp
 * Project: Leviathan
 * Version: 0.1
 * File Created: 07/04/2020 18:06
 * Author: Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * -----
 * Last Modified: 18/04/2020 16:10
 * Modified By: Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * -----
 * Copyright (c) 2020 - Alexandre THOMAS
 */

#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include "../Maths/vector2d.hpp"

class Board {
public:
    enum class Tile : char {
        ERR='e', EMPTY = ' ', WALL = '#', SNAKE_BODY = 'S', SNAKE_HEAD='H', FRUIT = 'O' 
    };

    Board(int size);
    ~Board();

    int size();

    Tile tile(int x, int y);
    Tile tile(Vector2D pos);
    void setTile(Tile tile, int x, int y);
    void setTile(Tile tile, Vector2D pos);
    Tile** grid();
    bool isOut(Vector2D& v);

    void print();

private:
    int m_size;
    Tile** m_grid;

    char toChar(Tile t);
};

#endif // BOARD_HPP