#include "Point.h"

Point::Point(const std::string& name, double x, double y):
    Shape(name), m_x(x), m_y(y)
{
}

double Point::x() const
{
    return 0.0;
}

void Point::setX(double x)
{
}

double Point::y() const
{
    return 0.0;
}

void Point::setY(double y)
{
}

void Point::translate(double deltaX, double deltaY)
{
}

void Point::translate(const std::pair<double, double>& delta)
{
}

void Point::translate(std::pair<double, double>&& delta)
{
}

double Point::distance(const Point& other) const
{
    return 0.0;
}
