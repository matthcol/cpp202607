#pragma once

#include <string>
#include <utility>

class Shape // abstract class car 1 methode virtuelle pure
{
private:
	std::string m_name;
protected:
	Shape(const std::string& name = std::string());
public:
	const std::string& name() const;
	void setName(std::string name);
	virtual void translate(double deltaX, double deltaY) =0; // methode virtuelle pure => "abtract"
	virtual void translate(const std::pair<double, double>& delta) = 0;
	virtual void translate(std::pair<double, double>&& delta) = 0;
};

