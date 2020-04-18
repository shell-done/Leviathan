/*
 * File: vector2d.hpp
 * Project: Leviathan
 * Version: 0.1
 * File Created: 07/04/2020 20:02
 * Author: Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * -----
 * Last Modified: 18/04/2020 16:10
 * Modified By: Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * -----
 * Copyright (c) 2020 - Alexandre THOMAS
 */

#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#include "vector.hpp"

class Vector2D : public Vector {
public:
    Vector2D(int defaultValue = 0);
    Vector2D(int x, int y);
    Vector2D(const Vector2D& v);

    int x();
    void setX(int x);

    int y();
    void setY(int y);

    void set(int x, int y);

    Vector2D operator+ (const Vector2D& v);
    Vector2D& operator+= (const Vector2D& v);
    Vector2D& operator= (const Vector2D& v);
};

#endif // VECTOR2D_HPP