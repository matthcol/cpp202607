#include "Circle.h"
#include <numbers>
//#include <iostream>

Circle::Circle(const std::string& name, double radius, const Point& center):
    Shape(name), m_radius(radius), m_center(center)
{
}

//Circle::~Circle()
//{
//    std::clog << "Circle destroyed: " << name() << std::endl;
//}

Circle::Circle(const std::string& name, double radius, Point&& center):
    Shape(name), m_radius(radius), m_center(center)
{
}

double Circle::radius() const
{
    return m_radius;
}

void Circle::setRadius(double radius)
{
    m_radius = radius;

}

const Point& Circle::center() const
{
    return m_center;
}

void Circle::setCenter(const Point& center)
{
    m_center = center;
}

void Circle::setCenter(Point&& center)
{
    m_center = center;
}

void Circle::translate(double deltaX, double deltaY)
{
    m_center.translate(deltaX, deltaY);
}


double Circle::area() const
{
    return std::numbers::pi * m_radius * m_radius;
}

double Circle::perimeter() const
{
    return 2.0 * std::numbers::pi * m_radius;
}
