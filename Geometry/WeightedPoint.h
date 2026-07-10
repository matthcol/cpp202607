#pragma once
#include "Point.h"

class WeightedPoint: public Point
{
private:
	double m_weight;

public:
	WeightedPoint(const std::string& name = std::string(), double x = 0.0, double y = 0.0, double weight = 1.0);
	virtual ~WeightedPoint() = default;

	double weight() const;
	void setWeight(double weight);

	auto operator<=>(const WeightedPoint& other) const = default;
};

template <>
struct std::formatter<WeightedPoint> : ShapeBaseFormatter {
	template<class FmtContext>
	auto format(const WeightedPoint& weighted_point, FmtContext& ctx) const {
		if (long_format) {
			return std::format_to(ctx.out(), 
				"WeightedPoint(name={}, x={}, y={}, weight={})", 
				weighted_point.name(), 
				weighted_point.x(), 
				weighted_point.y(),
				weighted_point.weight()
			);
		}
		else {
			return std::format_to(ctx.out(), 
				"{}({:0.3f}, {:0.3f})#{:0.3f}", 
				weighted_point.name(), 
				weighted_point.x(), 
				weighted_point.y(),
				weighted_point.weight()
			);
		}
	}
};

static_assert(std::formattable<WeightedPoint, char>, "formatter<WeightedPoint> missing or format() not const");
