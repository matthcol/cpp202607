#include "Point.h"
#include "itertools.h"
#include "WeightedPoint.h"
#include "Circle.h"
#include "Polygon.h"
#include "CMesurable2D.h"

#include <iostream>
#include <cstdlib>
#include <print>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <compare>
#include <algorithm>
#include <ranges>

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

void playWithWeightedPoints() {
	std::println();
	std::println("*************** W E I G T H E D   P O I N T S **************");
	WeightedPoint wp1;
	WeightedPoint wp2("W2", 3.5, 5.5, 10.0);
	std::println("{}, {}", wp1, wp2);
	std::println("{:l}, {:l}", wp1, wp2);
}

void playWithCircles() {
	std::println();
	std::println("*************** C I R C L E S **************");
	Circle c1;
	Point pA("A", 3.5, 4.5);
	Circle c2("C2", 10.0, pA);
	std::println("{}, {}", c1, c2);
	std::println("{:l}, {:l}", c1, c2);

	// LSP: Liskov (+Wing) Substitution Principle : en C++ uniqument en mode ref et pointer, sinon copy
	WeightedPoint wpW("W", 4.5, 12.25, 2.5);
	Circle c3("C3", 100.0, wpW); // NB: weighted est copié dans un point
	std::println("{:l}", wpW);
	std::println("{:l}", c3);

	Point pW = wpW; // copy
	Point& pt_ref = wpW;
	Shape& s_ref = wpW;
	// std::println("{}", pt_ref.weight); // là mais non visible
	std::println("As Point:", pt_ref.x());
	std::println("As Shape:", s_ref.name());

	Shape& s_ref2 = c3;
	IMesurable2D& m_ref = c3;
	std::println("As Shape:", s_ref2.name());
	std::println("As Mesurable2D:", m_ref.area());
}

void playWithShapes() {
	std::println();
	std::println("*************** S H A P E S **************");
	std::vector<std::unique_ptr<Shape>> shapes;
	shapes.push_back(std::make_unique<Point>("A", 1.5, 4.5));
	shapes.push_back(std::make_unique<Point>("B", 4.5, 12.5));
	shapes.push_back(std::make_unique<WeightedPoint>("WC", 4.5, 9.5, 2.5));
	shapes.push_back(std::make_unique<Circle>("C0", 10.0, Point("O")));
	shapes.push_back(std::make_unique<Circle>("C1", 12.5, Point("F", 4.5, 7.25)));
	shapes.push_back(std::make_unique<Polygon>());
	for (auto it = shapes.cbegin(), end = shapes.cend(); it != end; ++it) {
		const Shape* shape_ptr = it->get(); // observation
		std::println(" * {}", shape_ptr->name());

		if (const Point* pt_ptr = dynamic_cast<const Point*>(shape_ptr); pt_ptr != nullptr) {
			std::println("     - is a point: {:l}", *pt_ptr);
		}
		if (const WeightedPoint* wpt_ptr = dynamic_cast<const WeightedPoint*>(shape_ptr); wpt_ptr != nullptr) {
			std::println("     - is a weighted point: {:l}", *wpt_ptr);
		}
		if (const IMesurable2D* m2d_ptr = dynamic_cast<const IMesurable2D*>(shape_ptr); m2d_ptr != nullptr) {
			std::println("     - is mesurable in 2D: area={}, perimeter={}", m2d_ptr->area(), m2d_ptr->perimeter());
		}
	}

	for (auto it = shapes.cbegin(), end = shapes.cend(); it != end; ++it) { // le pointeur est const pas le shape !
		it->get()->translate(1.0, -1.0);
	}

} // destruction de tous les shapes

void playWithPolygons() {
	std::println();
	std::println("*************** P O L Y G O N S **************");
	Polygon poly0;
	Polygon poly1(
		"ABC", 
		{
			Point("A"),
			Point("B"),
			Point("C")
		}
	);
	std::deque stack_point{
			Point("D", 3.5, 12.25),
			Point("E", 6.5, 12.25),
			Point("F", 6.5, 8.25)
	};
	std::list list_point{
			Point("G"),
			Point("H"),
			Point("I")
	};
	Polygon poly2("DEF", stack_point.cbegin(), stack_point.cend());
	Polygon poly3("GHI", list_point);

	std::println("{}", poly1.name());
	std::println("{}", poly1[0]);

	poly1[0] = Point("J");
	std::println("{}", poly1[0]);

	const Polygon& poly_ref = poly1;
	//poly_ref[0] = Point("K");
	std::println("{}", poly_ref[0]);

	std::println("Vertices:");
	for (const auto& vertex: poly2){
		std::println(" - vertex: {}", vertex);
	}

	auto it = std::begin(poly3);

	std::println("Polygon (short format): {0}", poly2);
	std::println("Polygon (long format: vertices in short format): {0:l}", poly2);
	std::println("Polygon (long format / vertices in long format): {0:l:l}", poly2);
	std::println(" - perimeter = {}, area = {}", poly2.perimeter(), poly2.area());

	// concave polygon from Wikipedia shoelace formula article — expected area: 16.5
	Polygon polyWiki(
		"Shoelace",
		{
			Point("A", 1, 6),
			Point("B", 3, 1),
			Point("C", 7, 2),
			Point("D", 4, 4),
			Point("E", 8, 5)
		}
	);
	std::println("Polygon (short format): {0}", polyWiki);
	std::println("Polygon (long format: vertices in short format): {0:l}", polyWiki);
	std::println("Polygon (long format / vertices in long format): {0:l:l}", polyWiki);
	std::println(" - area = {} (expected 16.5)", polyWiki.area());

	std::vector<Polygon> polygons{ poly2, polyWiki }; // copies
	std::println();
	std::println("{}", polygons);
	std::println("{::l}", polygons);
	std::println("{:n:l}", polygons);
	std::println("{::l:l}", polygons);

	// convex quadrilateral
	Polygon polySquare(
		"Square",
		{
			Point("A", 0, 0),
			Point("B", 4, 0),
			Point("C", 4, 4),
			Point("D", 0, 4)
		}
	);

	// self-intersecting quadrilateral (bowtie)
	Polygon polyBowtie(
		"Bowtie",
		{
			Point("A", 0, 0),
			Point("B", 4, 4),
			Point("C", 4, 0),
			Point("D", 0, 4)
		}
	);

	auto printIndicators = [](const Polygon& p) {
		std::println(
			"{}: well_formed={}, crossed={}, convex={}, concave={}",
			p, p.isWellFormed(), p.isCrossed(), p.isConvex(), p.isConcave()
		);
	};

	std::println();
	std::println("--- indicators ---");
	printIndicators(poly0);      // degenerate
	printIndicators(poly2);      // triangle (convex)
	printIndicators(polyWiki);   // concave (Wikipedia shoelace)
	printIndicators(polySquare); // convex quadrilateral
	printIndicators(polyBowtie); // crossed
}


void playWithMesurables() {
	std::println();
	std::println("*************** M E S U R A B L E S **************");
	std::vector<std::unique_ptr<IMesurable2D>> shapes;
	shapes.push_back(std::make_unique<Circle>("C", 2.0, Point("A")));
	shapes.push_back(std::make_unique<Polygon>());


	Circle c2("C2", 2.0, Point("A"));
	double d = compacite(c2); // resolution de template => compacite<Circle>, no vtable
	std::println("compacite C2: {}", d);

	Polygon poly2(
		"DEF",
		{
			Point("D", 3.5, 12.25),
			Point("E", 6.5, 12.25),
			Point("F", 6.5, 8.25)
		}
	);
	double d2 = compacite(poly2);  // resolution de template => compacite<Polygon>, no vtable
	std::println("compacite Poly2: {}", d2);

	std::vector<std::unique_ptr<Shape>> shapes2;  
	// NB: constructor with initializer_list cannot be used here because copy is deleted on unique_ptr objects
	shapes2.push_back(std::make_unique<Circle>("C2", 10.0, Point("A")));
	shapes2.push_back(std::make_unique<Polygon>(
		Polygon(
			"Tri345",
			{
				Point("D", 3.5, 12.25),
				Point("E", 6.5, 12.25),
				Point("F", 6.5, 8.25)
			}
		))
	);
	shapes2.push_back(std::make_unique<Point>("A"));
	shapes2.push_back(std::make_unique<Polygon>(
		// concave polygon from Wikipedia shoelace formula article
		Polygon(
			"Shoelace",
			{
				Point("A", 1, 6),
				Point("B", 3, 1),
				Point("C", 7, 2),
				Point("D", 4, 4),
				Point("E", 8, 5)
			}
		))
	);

	auto mesurables = shapes2
		| std::views::transform([](const auto& s) {return dynamic_cast<const IMesurable2D*>(s.get()); }) // observator pointer
		| std::views::filter([](auto* p) { return p != nullptr; }) // auto * => oblige à vérifier que c'est 1 pointeur
		| std::views::transform([](auto* p) -> const IMesurable2D& {return *p; }); // type retoiur nécessaire pour déclencher la sémantique ref

	//double total = std::ranges::fold_left(
	//	mesurables,
	//	0.0,
	//	[](double acc, const CMesurable2D auto& m) { return acc + m.area(); });

	double total = totalArea(mesurables); 
	// resolution de template totalArea sur la view sur des const IMesurable&
	// compatible avec le concept CMesurable2D mais en mode vtable car derrière le type interface

	std::println("total area: {}", total);

	// copy all polygons from shapes2 into a flat vector<Polygon>
	std::vector<Polygon> polygons;
	auto polygon_ptrs = shapes2
		| std::views::transform([](const auto& s) { return dynamic_cast<const Polygon*>(s.get()); })
		| std::views::filter([](auto* p) { return p != nullptr; })
		| std::views::transform([](auto* p) -> const Polygon& { return *p; });
	std::ranges::copy(polygon_ptrs, std::back_inserter(polygons)); 
	// back_inserter allow to insert at the end instead of overwriting and have to allocate the exact number of elements 
	// before the filter algorithm

	std::println("Polygons copied ({})", polygons.size());
	for (const auto& poly : polygons) {
		std::println(" * {:l}", poly);
	}

	// V2: C++23 ranges::to — no back_inserter needed
	auto polygons2 = polygon_ptrs | std::ranges::to<std::vector<Polygon>>();
	std::println("Polygons copied v2 ({})", polygons2.size());
	for (const auto& poly : polygons2) {
		std::println(" * {:l}", poly);
	}
}

int main() {
	playWithPoints();
	playWithWeightedPoints();
	playWithCircles();
	playWithShapes();
	playWithPolygons();
	playWithMesurables();
	return EXIT_SUCCESS;
}