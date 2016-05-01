#ifndef __FPROJECTILE_HPP__
#define __FPROJECTILE_HPP__

#include <float.h>

#include "FObject.hpp"
#include "FTypes.hpp"

class FProjectile : public FObject
{
public:
	FProjectile(FVector, FVector, FProjectileType, float, bool, bool);
	void tick(float);
	FProjectileType getType();
	bool isAlive();
	
private:
	FProjectileType m_type;
	float m_time;
};

#endif
