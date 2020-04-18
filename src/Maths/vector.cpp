#include "vector.hpp"

Vector::Vector(int dim, float defaultValue) : m_dim(dim) {
    m_vector = new float[dim];

    for(int i=0; i<dim; i++)
        m_vector[i] = defaultValue;
}

Vector::Vector(const Vector& vector) : m_dim(vector.m_dim) {
    m_vector = new float[m_dim];

    for(int i=0; i<m_dim; i++)
        m_vector[i] = vector.m_vector[i];
}

Vector::~Vector() {
    delete[] m_vector;
}

int Vector::dim() {
    return m_dim;
}

float &Vector::operator[] (int i) {
    if(i >= m_dim)
        throw std::out_of_range("Attempting to get index " + std::to_string(i) + " in a " + std::to_string(m_dim) + "-dimensional vector");

    return m_vector[i];
}


Vector Vector::operator+ (const Vector& v) {
    if(m_dim != v.m_dim)
        throw MathException("Cannot add 2 vectors with 2 different dimensions");

    Vector res(m_dim);

    for(int i=0; i<m_dim; i++)
        res[i] = m_vector[i] + v.m_vector[i];

    return res;
}

Vector& Vector::operator+= (const Vector& v) {   
    if(m_dim != v.m_dim)
        throw MathException("Cannot add 2 vectors with 2 different dimensions");

    for(int i=0; i<m_dim; i++)
        m_vector[i] += v.m_vector[i];

    return *this;
}

Vector Vector::operator* (float a) {
    Vector res(m_dim);

    for(int i=0; i<m_dim; i++)
        res[i] = a*m_vector[i];

    return res;
}

Vector& Vector::operator*= (float a) {
    for(int i=0; i<m_dim; i++)
        m_vector[i] *= a;

    return *this;
}

Vector& Vector::operator= (const Vector& v) {
    if(m_dim != v.m_dim) {
        delete[] m_vector;

        m_dim = v.m_dim;
        m_vector = new float[m_dim];
    }

    for(int i=0; i<m_dim; i++) {
        m_vector[i] = v.m_vector[i];
    }
    
    return *this;
}

void Vector::print() {
    std::cout << "( ";

    for(int i=0; i<m_dim-1; i++)
        std::cout << m_vector[i] << ", ";

    std::cout << m_vector[m_dim-1] << " )" << std::endl;
}