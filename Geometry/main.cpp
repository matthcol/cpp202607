#include "Point.h"

#include <iostream>
#include <cstdlib>
#include <print>
#include <vector>
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

	std::vector<Point> points{ p0, pO, pA, pB };
	
	for (const auto& pt : points) {
		std::println("{}", pt);
		std::println("{:l}", pt);
		std::println(" - name: {}", pt.name());
		std::println(" - x: {}", pt.x());
		std::println(" - y: {}", pt.y());
	}

	print_range(points);
	for (auto& pt : points) {
		pt.translate(1, 2); // liaison tardive
	}
	print_range(points);
}

int main() {
	playWithPoints();
	return EXIT_SUCCESS;
}