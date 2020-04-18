/*
 * File: functions.hpp
 * Project: Leviathan
 * Version: 0.1
 * File Created: 11/04/2020 01:03
 * Author: Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * -----
 * Last Modified: 18/04/2020 16:10
 * Modified By: Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * -----
 * Copyright (c) 2020 - Alexandre THOMAS
 */

#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <cmath>
#include "../core.hpp"
#include "vector.hpp"
#include "matrix.hpp"

class Functions {
public:
    static float unit(float x);
    static void unit(Vector& v);

    static float ReLU(float x);
    static void ReLU(Vector& v);

    static float sigmoid(float x);
    static void sigmoid(Vector& v);
};

#endif // FUNCTIONS_HPP