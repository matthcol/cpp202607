#include "Movie.h"



// NB: on peut aussi definir que le constructeur à 3 paramètres
// avec valeurs par défaut pour year et duration

Movie::Movie(const std::string& title): Movie(title, 0, 0)
{
}

Movie::Movie(const std::string& title, std::uint16_t year): Movie(title, year, 0)
{
}

Movie::Movie(const std::string& title, std::uint16_t year, std::uint16_t duration): 
	m_title(title), m_year(year), m_duration(duration)
{
}

const std::string& Movie::title() const
{
	return m_title;
}

void Movie::setTitle(const std::string& title)
{
	m_title = title;
}

std::uint16_t Movie::year() const
{
	return m_year;
}

void Movie::setYear(std::uint16_t year)
{
	m_year = year;
}

std::uint16_t Movie::duration() const
{
	return m_duration;
}

void Movie::setDuration(std::uint16_t duration)
{
	m_duration = duration;
}

std::string Movie::toString() const
{
	// C++20
	return std::format("{}", *this); // utilise la surcharge de template formatter pour le type Movie
}

bool Movie::operator==(const Movie& other) const
{
	return (this->m_title == other.m_title)
		&& (this->m_year == other.m_year)
		&& (this->m_duration == other.m_duration);
}

std::weak_ordering Movie::operator<=>(const Movie& other) const
{
	if (auto cmp = this->m_year <=> other.m_year; cmp != std::partial_ordering::equivalent) return cmp;
	return this->m_title <=> other.m_title;
}

std::ostream& operator<<(std::ostream& out, const Movie& movie)
{
	 //return out << movie.toString();
	return out << movie.title() << " (" << movie.year() << ')';
}
