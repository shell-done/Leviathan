/*
 * File: vector.hpp
 * Project: Leviathan
 * Version: 0.1
 * File Created: 07/04/2020 19:46
 * Author: Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * -----
 * Last Modified: 18/04/2020 16:10
 * Modified By: Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * -----
 * Copyright (c) 2020 - Alexandre THOMAS
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include "math_exception.hpp"

class Vector {
public:
    Vector(int dim, float defaultValue = 0);
    Vector(const Vector& vector);
    ~Vector();

    int dim();
    float &operator[] (int i);
    Vector operator+ (const Vector& v);
    Vector& operator+= (const Vector& v);
    Vector operator* (float a);
    Vector& operator*= (float a);
    Vector& operator= (const Vector& v);

    void print();

protected:
    float* m_vector;

private:
    int m_dim;
};

#endif // VECTOR_H