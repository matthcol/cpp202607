#include "itertools.h"
#include "Movie.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <print>
#include <format>

//static_assert(std::formattable<Movie, char>, "1: formatter Movie invisible");
//static_assert(std::formattable<const Movie&, char>, "2: Movie pas formatable en const");
//static_assert(std::formattable<std::vector<Movie>, char>, "3: range formatting absent");


void useArrayC(double* temperatures, size_t size) {
	std::cout << "Array For-I:" << std::endl;
	for (size_t i = 0; i < size; i++) {
		double t = temperatures[i];
		std::cout << " - " << t << std::endl;
	}
}

void useArrayIt(double* first, double* last) {
	std::cout << "Array For-It:" << std::endl;
	for (; first != last; ++first) {
		double t = *first;
		std::cout << " - " << t << std::endl;
	}
}

void useVectorItForward(std::vector<double>::iterator first, std::vector<double>::iterator last) {
	std::cout << "Vector For-It:" << std::endl;
	for (; first != last; ++first) {
		double t = *first;
		std::cout << " - " << t << std::endl;
	}
}

void playWithArrays(size_t size) {
	// static arrays
	double temperatures1[]{ 12.5, 39.3, 45.7 };
	double temperatures2[] = { 25.2, 34.1, -10.5 };
	double temperatures3[10];
	// dynamic array
	double* temperatures4 = new double[size]; // NB: 10 peut etre un parametre

	std::cout << "Array 1:" << std::endl;
	for (auto t : temperatures1) {  // "for-each C++ 11"
		std::cout << " - " << t << std::endl;
	}
	std::cout << "Array 2:" << std::endl;
	for (auto t : temperatures2) {
		std::cout << " - " << t << std::endl;
	}
	std::cout << "Array 3:" << std::endl;
	for (auto t : temperatures3) {
		std::cout << " - " << t << std::endl;
	}
	std::cout << "Array 4:" << std::endl;
	//for (auto t : temperatures4) {  // Compilation Error
	//	std::cout << " - " << t << std::endl;
	//}
	for (size_t i = 0; i < size; i++) {
		double t = temperatures4[i];
		std::cout << " - " << t << std::endl;
	}

	useArrayC(temperatures1, 3);
	useArrayC(temperatures4, size);
	//useArrayC(temperatures1, 50); // faible debordement, si + => seg fault

	useArrayIt(std::begin(temperatures1), std::end(temperatures1));
	useArrayIt(std::begin(temperatures1) + 1, std::end(temperatures1) -1);
	useArrayIt(temperatures4, temperatures4 + size);

	displayIterableLegacy(std::begin(temperatures1), std::end(temperatures1));

	delete[] temperatures4;
}

void playWithVectorDouble() {
	std::vector<double> temperatures1{ 12.5, 39.3, 45.7, 13.4, 15.7, 18.5 };
	std::cout << "Vector 1: size " << temperatures1.size() << std::endl;
	for (auto t : temperatures1) {
		std::cout << " - " << t << std::endl;
	}
	temperatures1.push_back(25.2);
	std::cout << "Vector 1: size " << temperatures1.size() << std::endl;
	for (auto t : temperatures1) {
		std::cout << " - " << t << std::endl;
	}
	useVectorItForward(std::begin(temperatures1), std::end(temperatures1));
	useVectorItForward(temperatures1.begin(), temperatures1.end());
	useVectorItForward(temperatures1.begin() + 2, temperatures1.end() - 1);
	//useVectorItForward(temperatures1.rbegin(), temperatures1.rend()); // pb de type

	displayIterableLegacy(temperatures1.begin(), temperatures1.end());
	displayIterableLegacy(temperatures1.rbegin(), temperatures1.rend());
	displayIterableLegacy(temperatures1.begin() + 2, temperatures1.end() - 1);

	displayIterableSentinel(temperatures1.begin(), temperatures1.end());

	std::vector<double> temperatures2(temperatures1);
	//displayIterableSentinel(temperatures1.begin(), temperatures2.end()); // dynamic error
	displayIterableSentinel(temperatures2.begin() + 2, temperatures2.end() - 2);
	//displayIterableSentinel(temperatures2.begin() + 2, temperatures2.end() + 2); // dynamic error

	displayRange(temperatures1);

	// some algorithms until c++20
	auto it_last = temperatures1.end(); // -2
	auto it_found = std::find(temperatures1.begin(), it_last, 18.5);
	if (it_found != it_last) {
		std::cout << "Found value: " << *it_found << std::endl;
	}
	else {
		std::cout << "Not found value" << std::endl;
	}

	double temperature_threshold = 20;
	auto it_found_20 = std::find_if(temperatures1.begin(), it_last, [temperature_threshold](auto t) {return t >= temperature_threshold; });
	if (it_found_20 != it_last) {
		std::cout << "Found >= 20: " << *it_found_20 << std::endl;
	}
	else {
		std::cout << "Not found >= 20" << std::endl;
	}

	std::sort(temperatures1.begin(), temperatures1.end());
	displayRange(temperatures1);
	std::sort(temperatures1.begin(), temperatures1.end(), std::greater<double>());
	displayRange(temperatures1);

	// some algorithms since c++20
	std::ranges::sort(temperatures1);
}

void playWithVectorString() {
	std::vector<std::string> cities{ "Toulouse", "Narbonne", "Pau", "Nassau" };
	displayIterableLegacy(cities.begin(), cities.end());
	std::vector<std::u8string> words{ u8"東京", u8"🦜" };
	//displayIterable(words.begin(), words.end());

	//std::cout << cities << std::endl;
	std::println("Vecteur formatting:");
	std::println("{}\n", cities);
	std::println("{::}\n", cities);
	std::println("{:n}\n", cities);
	std::println("{:n:}\n", cities);
	std::println();
}

void helperMovie(const Movie& movie) {
	std::println("*************** Helper movie *******************");
	std::cout << movie.title() << ':' << std::endl;
}

void playWithMovies() {
	std::println();
	std::println("*************** Movies *******************");
	auto movie1 = Movie();
	std::println("title = {}", movie1.title());
	movie1.setTitle("Dune: Part Three");
	std::println("title = {}", movie1.title());

	//i.e: const std::string&
	auto& t = movie1.title();
	//t[0] = 'Z';

	Movie movie2("Autant en emporte le vent");
	Movie movie3("Le règne animal", 2023);
	Movie movie4("The Terminator", 1984, 107);

	// 2 constructeurs offerts : copy + move
	Movie movieClone(movie4); // constructeur copy (movie4 lvalue)
	//Movie movieMoved(std::move(movie1)); // move
	//Movie movie = mafonction(Movie())

	movieClone = movie3; // operateur copy
	movieClone = Movie("Star Wars"); // operateur move (rvalue)
	
	std::string title("Fast and Furious");
	movieClone = title; // conversion implicite avec constructeur Movie(const std::string& title)

	// TODO: display movie
	// TODO: vector<Movie>

	std::cout << movie1.toString() << std::endl;
	std::println("{}", movie1.toString());
	//println("{}", movie1.toString()); // no std

	std::cout << movie4 << std::endl;
	std::println("{}", movie1);

	print("{}", title);

	helperMovie(movie4);

	title = "Les 4 Fantastiques";
	helperMovie(title); // conversion implicite


	//const Movie *const *const *const *const movie_ptr = nullptr;
	//Movie const *const* const* const* movie_ptr;
	//const std::vector< const Movie *const *const *const *const> movies;


	std::println("{0}, {0:l}, {1:03d}", movie4, 17);
	std::println("{0}, {0:l}, {0:}", movie4);

	std::vector<Movie> movies{ movie1, movie2, movie3, movie4 }; // par copy
	std::vector<Movie> movies2{
		Movie("Rocky"),
		Movie("Rocky II"),
		Movie("Rocky III"),
		Movie("Rocky IV")
	}; // par move
	//std::vector<Movie&> movies3{ movie1, movie2, movie3, movie4 };
	std::vector<std::reference_wrapper<Movie>> movies3{ movie1, movie2, movie3, movie4 };
	std::vector<Movie*> movies4{ &movie1, &movie2, &movie3, &movie4 };
	displayRange(movies);
	displayRange(movies2);
	displayRange(movies3);
	displayRange(movies4);
	//std::println("{0:n:l}", movies);
}

void playReferencePointer() {
	Movie movie("Toy Story 5", 2026);
	Movie& movie_ref = movie;
	Movie* movie_ptr = &movie;
	Movie*& movie_ptr_ref = movie_ptr;
	//Movie&* movie_ref_ptr = &movie_ref; // pointer sur reference interdit
	std::reference_wrapper<Movie> movie_ref2 = movie;
	std::reference_wrapper<Movie>* movie_ref_ptr = &movie_ref2;
	std::println("{}", movie);
	std::println("{}", movie_ref);
	std::println("{}", movie_ref2.get());
	std::println("{}", *movie_ptr);
	std::println("{}", *movie_ptr_ref);
	std::println("{}", movie_ref_ptr->get());

	std::cout << movie_ref2.get().title();
	Movie& movie_ref3 = movie_ref2;
	Movie movie_copy = movie_ref2;
}

int main() {
	playWithArrays(11);
	playWithVectorDouble();
	playWithVectorString();
	playWithMovies();
	playReferencePointer();
	return EXIT_SUCCESS;
}