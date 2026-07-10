#pragma once

#include <string>
#include <utility>
#include <compare>
#include <format>

class Shape // abstract class car 1 methode virtuelle pure
{
private:
	std::string m_name;
protected:
	Shape(const std::string& name = std::string());
public:
	virtual ~Shape() = default;
	const std::string& name() const;
	void setName(std::string name);
	virtual void translate(double deltaX, double deltaY) =0; // methode virtuelle pure => "abtract"
	virtual void translate(const std::pair<double, double>& delta);
	virtual void translate(std::pair<double, double>&& delta);

	auto operator<=>(const Shape& other) const = default;
};



struct ShapeBaseFormatter {
	bool long_format = false;

	template<class ParseContext>
	constexpr auto parse(ParseContext& ctx) {
		auto it = ctx.begin();
		long_format = (it != ctx.end()) && *it == 'l';
		return it + long_format;
	}
};