#include "Polygon.h"
//#include <iostream>

//Polygon::~Polygon()
//{
//    std::clog << "Polygon destroyed: " << name() << std::endl;
//}

#include <algorithm>

Polygon::Polygon(const std::string& name):
    Shape(name), m_vertices(std::vector<Point>())
{
}

Polygon::Polygon(const std::string& name, std::initializer_list<Point> vertices) :
    Shape(name), m_vertices(vertices) 
{
}

Polygon::size_type Polygon::order() const
{
    return m_vertices.size();
}

const Point& Polygon::operator[](size_type index) const
{
    return m_vertices[index];
}

Point& Polygon::operator[](size_type index)
{
    return m_vertices[index];
}

Polygon::iterator Polygon::begin()
{
    return m_vertices.begin();
}

Polygon::iterator Polygon::end()
{
    return m_vertices.end();
}

Polygon::const_iterator Polygon::begin() const
{
    return m_vertices.begin();
}

Polygon::const_iterator Polygon::end() const
{
    return m_vertices.end();
}

Polygon::const_iterator Polygon::cbegin() const
{
    return m_vertices.cbegin();
}

Polygon::const_iterator Polygon::cend() const
{
    return m_vertices.cend();
}

void Polygon::translate(double deltaX, double deltaY)
{
    std::ranges::for_each(begin(), end(), [deltaX, deltaY](auto& v) { v.translate(deltaX, deltaY); });
}

double Polygon::area() const
{
    // shoelace formula (order >= 3, non crossed)
    auto prev = (order() == 0) ? this->cend() : this->cend() - 1;
    auto next = this->cbegin();
    auto end = this->cend();
    double res = 0.0;
    while (next != end) {
        res += next->x() * prev->y() - next->y() * prev->x();
        prev = next;
        ++next;
    }
    return abs(res) / 2.0;
}

double Polygon::perimeter() const
{
    auto prev = (order() == 0) ? this->cend() : this->cend() - 1;
    auto next = this->cbegin();
    auto end = this->cend();
    double res = 0.0;
    while (next != end) {
        res += prev->distance(*next);
        prev = next;
        ++next;
    }
    return res;
}
