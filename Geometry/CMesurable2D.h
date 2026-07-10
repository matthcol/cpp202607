#pragma once

#include <concepts>
#include <numbers>
#include <algorithm>
#include <ranges>

template<typename T>
concept CMesurable2D = requires(const T & t) {
	{ t.area() } -> std::convertible_to<double>;
	{ t.perimeter() } -> std::convertible_to<double>;
};

// NB: 2 following functions are considered as a template function with auto parameter
//  - if CMesurable2D auto = Circle => no vtable
//  - if CMesurable2D auto = Polygon => no vtable
//  - if CMesurable2D auto = IMesurable2D => vtable to decide dynamically if it's a Circle, Polygon or future other type

// NB: auto parameter => implicit template
double compacite(const CMesurable2D auto& m) {
	return 4 * std::numbers::pi * m.area() / (m.perimeter() * m.perimeter());
}

double totalArea(std::ranges::input_range auto&& shapes)
	requires CMesurable2D<std::ranges::range_value_t<decltype(shapes)>>
{
	return std::ranges::fold_left(shapes, 0.0,
		[](double acc, const auto& s) { return acc + s.area(); });
}
