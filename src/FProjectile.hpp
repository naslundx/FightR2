#ifndef __FPROJECTILE_HPP__
#define __FPROJECTILE_HPP__

#include <float.h>

#include "FObject.hpp"

class FProjectile : public FObject
{
public:
	FProjectile(FVector, FVector, int, float);
	void tick(float);
	int getType();
	bool isAlive();
	
private:
	int m_type;
	float m_time;
};

#endif
