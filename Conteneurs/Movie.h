#pragma once
#include <string>
#include <cstdint>
#include <format>
#include <iostream>
//#include <vector>

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
};

std::ostream& operator<<(std::ostream& out, const Movie& movie);
//std::ostream& operator<<(std::ostream& out, const Movie* movie);

// surcharge de template
// - fonction_utilisant_format("{0:xyz}", movie)
template <>
struct std::formatter<Movie> {
	bool long_format = false;

	constexpr auto parse(std::format_parse_context& ctx) {
		auto it = ctx.begin();
		long_format = (it != ctx.end()) && *it == 'l';
		return it + long_format; // + 0/1
	}

	auto format(const Movie& movie, std::format_context& ctx) const {
		if (long_format) {
			return std::format_to(ctx.out(), "Movie(title={}, year={}, duration={})", movie.title(), movie.year(), movie.duration());
		}
		else {
			return std::format_to(ctx.out(), "{} ({})", movie.title(), movie.year());
		}
	}
};

// on pourrait aussi faire :
//template <>
//struct std::formatter<std::vector<Movie>> {
//
//};

