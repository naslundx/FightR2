#include "FVector.hpp"

FVector::FVector()
{
	this->x = 0;
	this->y = 0;
}

FVector::FVector(double X, double Y)
{
	x = X;
	y = Y;
}
	
double FVector::getLength()
{
	return sqrt(x * x + y * y);
}

FVector FVector::operator + (const FVector& other)
{
	return FVector(x + other.x, y + other.y);
}

FVector FVector::operator - (const FVector& other)
{
	return FVector(x - other.x, y - other.y);
}

FVector FVector::operator - ()
{
	return FVector(-x, -y);
}

double FVector::operator * (const FVector& other)
{
	return x * other.x + y * other.y;
}

FVector FVector::operator * (const double& factor)
{
	return FVector(x * factor, y * factor);
}

FVector& FVector::operator += (const FVector& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

FVector& FVector::operator -= (const FVector& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

FVector& FVector::operator *= (const double& factor)
{
	x *= factor;
	y *= factor;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const FVector& obj)
{
	os << obj.x << "," << obj.y;
	return os;
}
