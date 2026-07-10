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

	auto operator<=>(const Point& other) const = default;
};

// formatter
template <>
struct std::formatter<Point> {
	bool long_format = false;

	template<class ParseContext>
	constexpr auto parse(ParseContext& ctx) {
		auto it = ctx.begin();
		long_format = (it != ctx.end()) && *it == 'l';
		return it + long_format; // + 0/1
	}

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

static_assert(__cplusplus > 202002L, "compilez en -std=c++23 !");  // pour MSVC, ajouter /Zc:__cplusplus
static_assert(std::formattable<Point, char>, "formatter<Point> absent ou format() non-const");

