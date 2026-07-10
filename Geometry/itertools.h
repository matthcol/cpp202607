#pragma once

#include <ranges>
#include <print>
#include <string_view>


template<std::forward_iterator I, std::sentinel_for<I> S>
	requires std::formattable<std::iter_value_t<I>, char>
void print_range(
	I first,
	S last,
	std::string_view intro = "",
	std::string_view sep = " ",
	std::string_view conclusion = "\n",
	std::iter_difference_t<I> max_display = 10
) {
	std::print("{}", intro);
	auto dist = std::ranges::distance(first, last);
	if (dist <= max_display) {
		if (first != last) {
			std::print("{}", *first);
			++first;
		}
		for (; first != last; ++first) {
			std::print("{}{}", sep, *first);
		}
	}
	else {
		auto delta = max_display / 2;
		print_range(first, std::ranges::next(first, delta), "", sep, " ... ", max_display);
		print_range(std::ranges::next(first, dist - delta), last, "", sep, "", max_display);
	}
	std::print("{}", conclusion);
}

template<std::ranges::input_range R> 
	requires std::formattable<std::ranges::range_value_t<R>, char>
void print_range(
	R&& r,
	std::string_view intro = "",
	std::string_view sep = " ",
	std::string_view conclusion = "\n",
	std::ranges::range_difference_t<R> max_display = 10
) {
	print_range(std::ranges::begin(r), std::ranges::end(r), intro, sep, conclusion, max_display);
}