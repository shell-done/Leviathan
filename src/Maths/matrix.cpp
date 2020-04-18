#include "matrix.hpp"
#include <string>
#include <iostream>

Matrix Matrix::Identity(int n) {
    Matrix m(n, n);

    for(int i=0; i<n; i++)
        m.m_matrix[i][i] = 1;

    return m;
}

Matrix::Matrix(int m, int n, int defaultValue) : m_m(m), m_n(n) {
    m_matrix = new float*[m];

    for(int i=0; i<m; i++) {
        m_matrix[i] = new float[n];
        
        for(int j=0; j<n; j++)
            m_matrix[i][j] = defaultValue;
    }
}

Matrix::Matrix(const Matrix& m) : m_m(m.m_m), m_n(m.m_n) {
    m_matrix = new float*[m_m];

    for(int i=0; i<m_m; i++) {
        m_matrix[i] = new float[m_n];
        
        for(int j=0; j<m_n; j++)
            m_matrix[i][j] = m.m_matrix[i][j];
    }
}

Matrix::~Matrix() {
    for(int i=0; i<m_m; i++) {
        delete[] m_matrix[i];
    }

    delete[] m_matrix;
}

int Matrix::m() {
    return m_m;
}

int Matrix::n() {
    return m_n;
}

float Matrix::el(int i, int j) {
    return m_matrix[i][j];
}

float Matrix::el(Vector2D& ij) {
    return el(ij.x(), ij.y());
}

void Matrix::setEl(int i, int j, float v) {
    m_matrix[i][j] = v;
}

void Matrix::setEl(Vector2D& ij, float v) {
    setEl(ij.x(), ij.y(), v);
}

bool Matrix::isSquare() {
    return m_m == m_n;
}

bool Matrix::isDiagonal() {
    if(!isSquare())
        return false;
    
    for(int i=0; i<m_m; i++)
        for(int j=0; j<m_n; j++)
            if(i != j && m_matrix[i][j] != 0)
                return false;

    return true;
}

Matrix Matrix::transpose() {
    Matrix t(m_n, m_n);

    for(int i=0; i<m_m; i++)
        for(int j=0; j<m_n; j++)
            t.setEl(j, i, m_matrix[i][j]);

    return t;
}

Matrix Matrix::operator+ (const Matrix& m) {
    if(m_m != m.m_m && m_n != m.m_n)
        throw MathException("Cannot add 2 matrix with 2 different dimensions");

    Matrix res(*this);

    for(int i=0; i<m_m; i++)
        for(int j=0; j<m_n; j++)
            res.setEl(i, j, m_matrix[i][j] + m.m_matrix[i][j]);

    return res;
}

Matrix& Matrix::operator+= (const Matrix& m) {
    if(m_m != m.m_m && m_n != m.m_n)
        throw MathException("Cannot add 2 matrix with 2 different dimensions");

    for(int i=0; i<m_m; i++)
        for(int j=0; j<m_n; j++)
            m_matrix[i][j] += m.m_matrix[i][j];

    return *this;
}

Matrix Matrix::operator* (const int& a) {
    Matrix res(*this);

    for(int i=0; i<m_m; i++)
        for(int j=0; j<m_n; j++)
            res.setEl(i, j, a * m_matrix[i][j]);

    return res;
}

Matrix& Matrix::operator*= (const int& a) {
    for(int i=0; i<m_m; i++)
        for(int j=0; j<m_n; j++)
            m_matrix[i][j] *= a;

    return *this;
}

Matrix Matrix::operator* (const Matrix& m) {
    if(m_n != m.m_m)
        throw MathException("Multiplication of two matrices is defined if and only if the number of columns of the left matrix is the same as the number of rows of the right matrix");

    Matrix res(m_m, m.m_n);

    for(int i=0; i<m_m; i++) {
        for(int j=0; j<m.m_n; j++) {
            float sum = 0;

            for(int r=0; r<m_n; r++) {
                sum += m_matrix[i][r] * m.m_matrix[r][j];
            }

            res.setEl(i, j, sum);
        }
    }

    return res;
}

Vector Matrix::operator* (Vector& v) {
    if(m_n != v.dim())
        throw MathException("Multiplication of two matrices is defined if and only if the number of columns of the left matrix is the same as the number of rows of the right matrix");

    Vector res(m_m);

    for(int i=0; i<m_m; i++) {
        float sum = 0;

        for(int r=0; r<m_n; r++) {
            sum += v[r] * m_matrix[i][r];
        }

        res[i] = sum;
    }

    return res;
}

Matrix& Matrix::operator= (const Matrix& m) {
    if(m_m != m.m_m || m_n != m.m_n) {
        for(int i=0; i<m_m; i++) {
            delete[] m_matrix[i];
        }

        delete[] m_matrix;

        m_m = m.m_m;
        m_n = m.m_n;
    }

    m_matrix = new float*[m_m];

    for(int i=0; i<m_m; i++) {
        m_matrix[i] = new float[m_n];
        
        for(int j=0; j<m_n; j++)
            m_matrix[i][j] = m.m_matrix[i][j];
    }
    
    return *this;
}