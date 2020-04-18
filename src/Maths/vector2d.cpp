#include "vector2d.hpp"

Vector2D::Vector2D(int x, int y) : Vector(2) {
    m_vector[0] = x;
    m_vector[1] = y;
}

Vector2D::Vector2D(int defaultValue) : Vector2D(defaultValue, defaultValue) { }

Vector2D::Vector2D(const Vector2D& v) : Vector2D(v.m_vector[0], v.m_vector[1]) {}

int Vector2D::x() { return m_vector[0]; }
void Vector2D::setX(int x) { m_vector[0] = x; }

int Vector2D::y() { return m_vector[1]; }
void Vector2D::setY(int y) { m_vector[1] = y; }

void Vector2D::set(int x, int y) {
    m_vector[0] = x;
    m_vector[1] = y;
}

Vector2D Vector2D::operator+ (const Vector2D& v) {
    Vector2D res;

    for(int i=0; i<2; i++)
        res[i] = m_vector[i] + v.m_vector[i];

    return res;
}

Vector2D& Vector2D::operator+= (const Vector2D& v) {
    m_vector[0] += v.m_vector[0];
    m_vector[1] += v.m_vector[1];

    return *this;
}

Vector2D& Vector2D::operator= (const Vector2D& v) {
    m_vector[0] = v.m_vector[0];
    m_vector[1] = v.m_vector[1];

    return *this;
}