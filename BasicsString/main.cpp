#include <iostream>
#include <string>
#include <print>
#include <memory>

// NB: on purpose no const definition

void referenceUse(std::string& city) { // reference
	std::println("[REF] {} at address {}, size {}", city, (void*)&city, city.size());
}

void sharedUse(std::shared_ptr<std::string> city_ptr) { // copy (cpt++): cpt > 0 => cpt > 1 
 	std::println("[SHARED] {} at address {}, variable at address {}, counter {}, size {}",
		*city_ptr,
		(void*)city_ptr.get(), 
		(void*)&city_ptr,
		city_ptr.use_count(), 
		city_ptr->size() 
	);
} //depilement de city_ptr => cpt-- => cpt > 0 => pas de delete

void borrowedUse(std::unique_ptr<std::string> city_ptr) { // move (prend possesion de l'objet)
	std::println("[UNIQUE] {} at address {}, variable at address {}, size {}",
		*city_ptr,
		(void*)city_ptr.get(), 
		(void*)&city_ptr,
		city_ptr->size() 
	);
} // dernier possesseur => delete

void playWithStrings() {
	// stack objects
	std::basic_string<char> word = "Hello";
	std::string emptyWord; // default constructor
	std::string cityFr1 = "Toulouse"; // constructor string(char*)
	std::string cityFr2("Narbonne"); // constructor string(char*)
	auto cityFr3 = std::string("Pau"); // constructor string(char*)
	std::u8string cityJp4 = u8"東京"; // need to parse source code in UTF-8
	std::u8string sentence = u8"I \u2661 \U0001F99C";
	const char* cityJpPrintable = reinterpret_cast<const char*>(cityJp4.c_str());
	const char* sentencePrintable = reinterpret_cast<const char*>(sentence.c_str());
	// dynamic object: Heap
	std::string* city5_ptr = new std::string("Nassau");
	// auto = std::shared_ptr<std::string>
	auto city6_ptr = std::make_shared<std::string>("Bayeux");
	// auto = std::unique_ptr<std::string>
	auto city7_ptr = std::make_unique<std::string>("Las Vegas");

	std::println("From {} to {}\n", cityFr1, cityJpPrintable);
	std::println("{}", sentencePrintable);
	std::string::size_type wordSize = cityFr1.size();
	auto wordSizeBis = cityFr1.size();
	std::println("{}: {} characters", cityFr1, cityFr1.size());
	std::println("{}: {} characters", cityJpPrintable, cityJp4.size());
	std::println("{}: {} characters", *city5_ptr, city5_ptr->size());

	// view some memory adresses
	std::println("{} at address {}", cityFr1, (void *) & cityFr1);
	std::println("{} at address {}, variable at address {}, size {}", 
		*city5_ptr, 
		(void *) city5_ptr, 
		(void *) &city5_ptr,
		city5_ptr->size()
	);
	std::println("{} at address {}, variable at address {}, counter {}, size {}", 
		*city6_ptr, 
		(void*) city6_ptr.get(), // methode du std:shared_ptr => display, debug only
		(void*) &city6_ptr,
		city6_ptr.use_count(),
		city6_ptr->size() // methode du stype std::string
	);
	std::println("{} at address {}, variable at address {}, size {}",
		*city7_ptr,
		(void*)city7_ptr.get(), // methode du std:shared_ptr => display, debug only
		(void*)&city7_ptr,
		city7_ptr->size() // methode du stype std::string
	);

	sharedUse(city6_ptr); // appel par copie (smart pointer)
	std::println("{} at address {}, variable at address {}, counter {}, size {}",
		*city6_ptr,
		(void*)city6_ptr.get(), // methode du std:shared_ptr => display, debug only
		(void*)&city6_ptr,
		city6_ptr.use_count(),
		city6_ptr->size() // methode du stype std::string
	);

	borrowedUse(std::move(city7_ptr));

	// city7_ptr a perdu l'objet => empty
	// NB: linter signale une possible mauvaise utilisation 
	// => msvc: flag /analyze
	//    clang: --analyze
	//    g++: pas de flag => clang-tidy -checks=bugprone-use-after-move
	std::println("variable at address {}, valeur ptr {}",
		(void*)&city7_ptr,  // NB: debug only
		(void*)city7_ptr.get() // null_ptr  // NB: debug only
	);

	referenceUse(cityFr1); // passage de parametre par reference

	//std::string& city_ref;  // compilation error
	std::string& city_ref = cityFr1;  // ok
	//std::string& city_ref = *city7_ptr; // NB: linter signale une possible mauvaise utilisation

	std::println("[LOCAL REF] {} at address {}, size {}", city_ref, (void*)&city_ref, city_ref.size());

	delete city5_ptr; // 1. call destructor ~string + 2. desallocation du string
}
// for all objects in the stack of this functions (parameters + local variables)
//		destructor is called (y compris les smart pointers)
//         - shared city_6 => delete

int main() {
	playWithStrings();
	return EXIT_SUCCESS;
}