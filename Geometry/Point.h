#pragma once
#include "Shape.h"

#include <format>
#include <compare>

class Point: public Shape
{
private:
	double m_x;
	double m_y;
public:
	// constructor full with default values
	explicit Point(const std::string& name = std::string(), double x = 0, double y = 0);
	virtual ~Point() = default;

	// getter + setter
	double x() const;
	void setX(double x);
	double y() const;
	void setY(double y);

	// implements translate
	virtual void translate(double deltaX, double deltaY) override; 

	double distance(const Point& other) const;

	auto operator<=>(const Point& other) const = default;
};

// formatter
template <>
struct std::formatter<Point> : ShapeBaseFormatter {
	template<class FmtContext>
	auto format(const Point& point, FmtContext& ctx) const {
		if (long_format) {
			return std::format_to(ctx.out(), "Point(name={}, x={}, y={})", point.name(), point.x(), point.y());
		}
		else {
			return std::format_to(ctx.out(), "{}({:0.3f}, {:0.3f})", point.name(), point.x(), point.y());
		}
	}
};

static_assert(__cplusplus > 202002L, "compile with -std=c++23 (MSVC: add /Zc:__cplusplus)");
static_assert(std::formattable<Point, char>, "formatter<Point> missing or format() not const");

