#pragma once
#include <string>
#include <cstdint>
#include <format>
#include <iostream>
//#include <vector>
#include <compare>

class Movie {
private:
	std::string m_title;
	std::uint16_t m_year;
	std::uint16_t m_duration;

public:
	Movie() = default;
	//explicit Movie(const std::string& title); // pour empecher conversion implicite std::string => Movie
	Movie(const std::string& title);
	Movie(const std::string& title, std::uint16_t year);
	Movie(const std::string& title, std::uint16_t year, std::uint16_t duration);

	// Option: remove copy or move mechanism
	//Movie(const Movie& movie) = delete; // enleve le constructeur par copie et l'assignation par copie
	//Movie(Movie&& movie) = delete;  // enleve le constructeur par movie et l'assignation par move

	const std::string& title() const;
	void setTitle(const std::string& title);

	std::uint16_t year() const;
	void setYear(std::uint16_t year);

	std::uint16_t duration() const;
	void setDuration(std::uint16_t duration);

	std::string toString() const;

	// std::strong_ordering operator<=>(const Movie& other) const = default; 
	// => generate 6 operateurs legacy: == != < <= > >=

	bool operator==(const Movie& other) const;  // generate: == et !=
	std::weak_ordering operator<=>(const Movie& other) const; // generate: < <= > >=
};

std::ostream& operator<<(std::ostream& out, const Movie& movie);
//std::ostream& operator<<(std::ostream& out, const Movie* movie);

// surcharge de template
// - fonction_utilisant_format("{0:xyz}", movie)
template <>
struct std::formatter<Movie> {
	bool long_format = false;

	template<class ParseContext>
	constexpr auto parse(ParseContext& ctx) {
		auto it = ctx.begin();
		long_format = (it != ctx.end()) && *it == 'l';
		return it + long_format; // + 0/1
	}

	template<class FmtContext>
	auto format(const Movie& movie, FmtContext& ctx) const {
		if (long_format) {
			return std::format_to(ctx.out(), "Movie(title={}, year={}, duration={})", movie.title(), movie.year(), movie.duration());
		}
		else {
			return std::format_to(ctx.out(), "{} ({})", movie.title(), movie.year());
		}
	}
};

static_assert(std::formattable<Movie, char>);
static_assert(std::formattable<Movie&, char>);
static_assert(std::formattable<const Movie&, char>);