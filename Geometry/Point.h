#pragma once
#include "Shape.h"

#include <format>

class Point: public Shape
{
private:
	double m_x;
	double m_y;
public:
	// constructor full with default values
	explicit Point(const std::string& name = std::string(), double x = 0, double y = 0);

	// getter + setter
	double x() const;
	void setX(double x);
	double y() const;
	void setY(double y);

	// implements translate
	virtual void translate(double deltaX, double deltaY) override; 
	virtual void translate(const std::pair<double, double>& delta) override;
	virtual void translate(std::pair<double, double>&& delta) override;

	double distance(const Point& other) const;
};

// formatter
template <>
struct std::formatter<Point> {
	bool long_format = false;

	constexpr auto parse(std::format_parse_context& ctx) {
		auto it = ctx.begin();
		long_format = (it != ctx.end()) && *it == 'l';
		return it + long_format; // + 0/1
	}

	auto format(const Point& point, std::format_context& ctx) const {
		if (long_format) {
			return std::format_to(ctx.out(), "Point(name={}, x={}, y={})", point.name(), point.x(), point.y());
		}
		else {
			return std::format_to(ctx.out(), "{}({:0.3f}, {:0.3f})", point.name(), point.x(), point.y());
		}
	}
};

