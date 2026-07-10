#include "Point.h"

#include <iostream>
#include <cstdlib>
#include <print>
#include <vector>
#include <set>
#include <compare>
#include "itertools.h"




void playWithPoints() {
	std::println();
	std::println("*************** P O I N T S **************");
	Point p0;
	Point pO("O");
	Point pA("A", 12.5, 25.25);
	Point pB("B", 16.5, 22.25);

	//std::string name = "Z";
	//Point pZ = name; // forbidden if constructor is explicit

	double d = pA.distance(pB);
	std::println("\ndistance: {}\n", d);

	std::vector<Point> points{ p0, pO, pA, pB };
	
	std::println("Points [init]:");
	for (const auto& pt : points) {
		std::println(" * {}", pt);
		std::println("   {:l}", pt);
		std::println("     - name: {}", pt.name());
		std::println("     - x: {}", pt.x());
		std::println("     - y: {}", pt.y());
	}
	std::println();

	print_range(points, "[Before translate] ", ", ");
	for (auto& pt : points) {
		pt.translate(1, 2); // liaison tardive
	}
	print_range(points, "[After] ", ", ");

	// auto = std::partial_ordering (double)
	auto cmp = pA <=> pB;

	std::set<Point> pointSet(std::from_range, points); // since C++20 (range)
	//std::set<Point>(points.cbegin(), points.cend()); // until C++20
	print_range(pointSet, "[Sorted Set] ", ", ");

	auto byCoords = [](const auto& pt1, const auto& pt2) {
		auto cmp = pt1.x() <=> pt2.x();
		if (cmp != std::partial_ordering::equivalent) {
			return std::is_lt(cmp);
		}
		cmp = pt1.y() <=> pt2.y();
		if (cmp != std::partial_ordering::equivalent) {
			return std::is_lt(cmp);
		}
		cmp = pt1.name() <=> pt2.name();
		return std::is_lt(cmp);
	};
	std::set<Point, decltype(byCoords)> pointSet2(std::from_range, points, byCoords);
	print_range(pointSet2, "[Sorted Set xy] ", ", ");

	std::println("{:n:l}", points);
}

int main() {
	playWithPoints();
	return EXIT_SUCCESS;
}