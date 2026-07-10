#pragma once
#include "Shape.h"
#include "IMesurable2D.h"
#include "Point.h"

#include <vector>
#include <ranges>
#include <iterator>

class Polygon :
    public Shape,
    public IMesurable2D
{
private:
    std::vector<Point> m_vertices;
    friend struct std::formatter<Polygon>;
public:
    using size_type = std::vector<Point>::size_type;
    // todo: types iterators
    using iterator = std::vector<Point>::iterator;
    using const_iterator = std::vector<Point>::const_iterator;

    explicit Polygon(const std::string& name = std::string()); // degenerated or triangle

    Polygon(const std::string& name, std::initializer_list<Point> vertices);
    
    template<std::input_iterator I, std::sentinel_for<I> S>
    Polygon(const std::string& name, I first, S last) :
        Shape(name), m_vertices(first, last)
    {

    }

    template<std::ranges::input_range R>
    Polygon(const std::string& name, R&& r) :
        Shape(name), m_vertices(std::from_range, r)
    {

    }
    
    virtual ~Polygon() = default;

    size_type order() const;
    const Point& operator[](size_type index) const;
    Point& operator[](size_type index);

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

    const_iterator cbegin() const;
    const_iterator cend() const;

    // Hérité via Shape
    void translate(double deltaX, double deltaY) override;

    // Hérité via IMesurable2D
    double area() const override;
    double perimeter() const override;
};

template <>
struct std::formatter<Polygon> : ShapeBaseFormatter {
    template<class FmtContext>
    auto format(const Polygon& polygon, FmtContext& ctx) const {
        if (long_format) {
            return std::format_to(ctx.out(),
                "Polygon(name={}, order={}, vertices={::l})", // todo: l et ll
                polygon.name(),
                polygon.order(),
                polygon.m_vertices
            );
        }
        else {
            return std::format_to(ctx.out(),
                "{}<o:{}>",
                polygon.name(),
                polygon.order()
            );
        }
    }
};

static_assert(std::formattable<Polygon, char>, "formatter<Polygon> missing or format() not const");
static_assert(std::ranges::random_access_range<Polygon>);
static_assert(std::ranges::random_access_range<const Polygon>);
static_assert(std::ranges::sized_range<Polygon>);
