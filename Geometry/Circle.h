#pragma once
#include "Shape.h"
#include "IMesurable2D.h"
#include "Point.h"
#include <string>

class Circle :
    public Shape,
    public IMesurable2D
{
private:
    double m_radius;
    Point m_center; // composition
public:
	Circle(const std::string& name = std::string(), double radius = 1.0, Point&& center = Point());
    Circle(const std::string& name, double radius, const Point& center);
    
    virtual ~Circle() = default;

    double radius() const;
    void setRadius(double radius);

    const Point& center() const;
    void setCenter(const Point& center);
    void setCenter(Point&& center);

    // Inherited from Shape
    void translate(double deltaX, double deltaY) override;

    // Inherited from IMesurable2D
    double area() const override;
    double perimeter() const override;

    auto operator<=>(const Circle& other) const = default;
};

template <>
struct std::formatter<Circle> : ShapeBaseFormatter {
	template<class FmtContext>
	auto format(const Circle& circle, FmtContext& ctx) const {
		if (long_format) {
			return std::format_to(ctx.out(),
				"Circle(name={}, radius={}, center={:l})",
				circle.name(),
				circle.radius(),
				circle.center()
			);
		}
		else {
			return std::format_to(ctx.out(),
				"{}<r:{}, c:{}>",
				circle.name(),
				circle.radius(),
				circle.center()
			);
		}
	}
};

static_assert(std::formattable<Circle, char>, "formatter<Circle> missing or format() not const");
