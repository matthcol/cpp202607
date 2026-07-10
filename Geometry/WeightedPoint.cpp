#include "WeightedPoint.h"

#include <format>
//#include <iostream>


WeightedPoint::WeightedPoint(const std::string& name, double x, double y, double weight): 
	Point(name, x, y), 
	m_weight(weight)
{
}

//WeightedPoint::~WeightedPoint()
//{
//	std::clog << "WeightedPoint destroyed: " << name() << std::endl;
//}

double WeightedPoint::weight() const
{
	return m_weight;
}

void WeightedPoint::setWeight(double weight)
{
	m_weight = weight;
}
