#include "Point.h"

#include <cmath>

Point::Point(const std::string& name, double x, double y):
    Shape(name), m_x(x), m_y(y)
{
}

double Point::x() const
{
    return m_x;
}

void Point::setX(double x)
{
    m_x = x;
}

double Point::y() const
{
    return m_y;
}

void Point::setY(double y)
{
    m_y = y;
}

void Point::translate(double deltaX, double deltaY)
{
    m_x += deltaX;
    m_y += deltaY;
}

void Point::translate(const std::pair<double, double>& delta)
{
    translate(delta.first, delta.second);
}

void Point::translate(std::pair<double, double>&& delta)
{
    translate(delta.first, delta.second);
}

double Point::distance(const Point& other) const
{
    return std::hypot(this->m_x - other.m_x, this->m_y - other.m_y);
}
