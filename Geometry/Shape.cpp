#include "Shape.h"
//#include <iostream>


Shape::Shape(const std::string& name): m_name(name)
{
}

//Shape::~Shape()
//{
//	std::clog << "Shape destroyed: " << m_name << std::endl;
//}

const std::string& Shape::name() const
{
	return m_name;
}

void Shape::setName(std::string name)
{
	m_name = name;
}

void Shape::translate(const std::pair<double, double>& delta)
{
	translate(delta.first, delta.second);
}

void Shape::translate(std::pair<double, double>&& delta)
{
	translate(delta.first, delta.second);
}
