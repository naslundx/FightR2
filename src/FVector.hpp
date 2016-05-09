#ifndef __FVECTOR_HPP__
#define __FVECTOR_HPP__

#include <cmath>
#include <iostream>

class FVector
{
public:
	FVector();
	FVector(double, double);
	
	double getLength();
	FVector operator + (const FVector&);
	FVector& operator += (const FVector&);
	FVector operator - (const FVector&);
	FVector& operator -= (const FVector&);
	FVector operator - ();
	double operator * (const FVector&);
	FVector operator * (const double&);
	FVector operator / (const double&);
	FVector& operator *= (const double&);
	
	bool clampTo(const float, const float, const float, const float);

	double x, y;
};

std::ostream& operator<<(std::ostream& os, const FVector& obj);

#endif
