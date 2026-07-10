#pragma once
class IMesurable2D
{
public:
	virtual ~IMesurable2D() =default; // add virtual clause
	virtual double area() const = 0;
	virtual double perimeter() const = 0;
};

