#pragma once

#include<iostream>
#include <ranges>

template<class InputIterator>
void displayIterableLegacy(InputIterator first, InputIterator last) {
	std::cout << "Iterable Legacy:" << std::endl;
	for (; first != last; ++first) {
		auto t = *first;
		std::cout << " - " << t << std::endl;
	}
}

// C++ 20 : concepts d'iterateurs, sentinelles, ranges

template<std::input_iterator I, std::sentinel_for<I> S>
void displayIterableSentinel(I first, S last) {
	std::cout << "Iterable Sentinel:" << std::endl;
	for (; first != last; ++first) {
		auto t = *first;
		std::cout << " - " << t << std::endl;
	}
}

template<std::ranges::input_range R>
void displayRange(R&& r) {
	auto first = std::ranges::begin(r);
	auto last = std::ranges::end(r);
	std::cout << "Range:" << std::endl;
	for (; first != last; ++first) {
		auto t = *first;
		std::cout << " - " << t << std::endl;
	}
}