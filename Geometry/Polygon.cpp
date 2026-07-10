#include "Polygon.h"
//#include <iostream>

//Polygon::~Polygon()
//{
//    std::clog << "Polygon destroyed: " << name() << std::endl;
//}

#include <algorithm>
#include <limits>

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
    if (!isWellFormed() || isCrossed())
        return std::numeric_limits<double>::quiet_NaN();
    // shoelace formula (order >= 3, non crossed)
    auto prev = this->cend() - 1;
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
    if (!isWellFormed())
        return std::numeric_limits<double>::quiet_NaN();
    auto prev = this->cend() - 1;
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

bool Polygon::isConcave() const
{
    return isWellFormed() && !isCrossed() && !isConvex();
}

bool Polygon::isConvex() const
{
    if (!isWellFormed()) return false;
    size_type n = m_vertices.size();

    int sign = 0;
    for (size_type i = 0; i < n; ++i) {
        const Point& a = m_vertices[i];
        const Point& b = m_vertices[(i + 1) % n];
        const Point& c = m_vertices[(i + 2) % n];
        double cross = (b.x() - a.x()) * (c.y() - b.y())
                     - (b.y() - a.y()) * (c.x() - b.x());
        if (cross != 0.0) {
            int s = (cross > 0) ? 1 : -1;
            if (sign == 0) sign = s;
            else if (sign != s) return false;
        }
    }
    return true;
}

bool Polygon::isCrossed() const
{
    if (!isWellFormed()) return false;
    size_type n = m_vertices.size();
    if (n < 4) return false; // triangle: all edge pairs are adjacent

    auto orientation = [](const Point& p, const Point& q, const Point& r) -> int {
        double val = (q.y() - p.y()) * (r.x() - q.x())
                   - (q.x() - p.x()) * (r.y() - q.y());
        if (val == 0.0) return 0;
        return (val > 0) ? 1 : 2;
    };

    auto onSegment = [](const Point& p, const Point& q, const Point& r) -> bool {
        return q.x() <= std::max(p.x(), r.x()) && q.x() >= std::min(p.x(), r.x())
            && q.y() <= std::max(p.y(), r.y()) && q.y() >= std::min(p.y(), r.y());
    };

    auto intersects = [&](size_type i, size_type j) -> bool {
        const Point& p1 = m_vertices[i];
        const Point& q1 = m_vertices[(i + 1) % n];
        const Point& p2 = m_vertices[j];
        const Point& q2 = m_vertices[(j + 1) % n];

        int d1 = orientation(p2, q2, p1);
        int d2 = orientation(p2, q2, q1);
        int d3 = orientation(p1, q1, p2);
        int d4 = orientation(p1, q1, q2);

        if (d1 != d2 && d3 != d4) return true;

        if (d1 == 0 && onSegment(p2, p1, q2)) return true;
        if (d2 == 0 && onSegment(p2, q1, q2)) return true;
        if (d3 == 0 && onSegment(p1, p2, q1)) return true;
        if (d4 == 0 && onSegment(p1, q2, q1)) return true;

        return false;
    };

    for (size_type i = 0; i < n; ++i) {
        for (size_type j = i + 2; j < n; ++j) {
            if (i == 0 && j == n - 1) continue; // wrap-around: edges 0 and n-1 share vertex[0]
            if (intersects(i, j)) return true;
        }
    }
    return false;
}
