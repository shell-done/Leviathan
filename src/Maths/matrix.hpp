/*
 * File: matrix.hpp
 * Project: Leviathan
 * Version: 0.1
 * File Created: 07/04/2020 18:44
 * Author: Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * -----
 * Last Modified: 18/04/2020 16:10
 * Modified By: Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * -----
 * Copyright (c) 2020 - Alexandre THOMAS
 */

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "vector.hpp"
#include "vector2d.hpp"

class Matrix {
public:
    static Matrix Identity(int n);

    Matrix(int m, int n, int defaultValue = 0);
    Matrix(const Matrix& matrix);
    ~Matrix();

    int m();
    int n();

    float el(int i, int j);
    float el(Vector2D& ij);
    void setEl(int i, int j, float value);
    void setEl(Vector2D& ij, float value);

    bool isSquare();
    bool isDiagonal();

    Matrix transpose();

    Matrix operator+ (const Matrix& m);
    Matrix& operator+= (const Matrix& m);
    Matrix operator* (const int& a);
    Matrix& operator*= (const int& a);
    Matrix operator* (const Matrix& m);
    Vector operator* (Vector& v);
    Matrix& operator= (const Matrix& v);

private:
    int m_m;
    int m_n;

    float** m_matrix;
};

#endif // MATRIX_HPP