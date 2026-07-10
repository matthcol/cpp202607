#pragma once
#include "Point.h"
#include <ranges>

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

	template<std::input_iterator I, std::sentinel_for<I> S>
		requires std::derived_from<std::iter_value_t<I>, WeightedPoint>
	static WeightedPoint barycentre(I first, S last, const std::string& name = "bary") {
		double totalWeight = 0.0, wx = 0.0, wy = 0.0;
		for (auto it = first; it != last; ++it) {
			totalWeight += it->weight();
			wx += it->weight() * it->x();
			wy += it->weight() * it->y();
		}
		if (totalWeight == 0.0)
			return WeightedPoint(name);
		return WeightedPoint(name, wx / totalWeight, wy / totalWeight, totalWeight);
	}

	template<std::ranges::input_range R>
		requires std::derived_from<std::ranges::range_value_t<R>, WeightedPoint>
	static WeightedPoint barycentre(R&& range, const std::string& name = "bary") {
		return barycentre(std::ranges::begin(range), std::ranges::end(range), name);
	}
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
