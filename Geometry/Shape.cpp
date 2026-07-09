#include "Shape.h"



Shape::Shape(const std::string& name): m_name(name)
{
}

const std::string& Shape::name() const
{
	return m_name;
}

void Shape::setName(std::string name)
{
	m_name = name;
}
