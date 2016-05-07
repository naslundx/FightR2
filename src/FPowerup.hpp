#ifndef __FPOWERUP_HPP__
#define __FPOWERUP_HPP__

#include <float.h>

#include "FObject.hpp"
#include "FTypes.hpp"

class FPowerup : public FObject
{
public:
	FPowerup(FVector, FVector, FPowerupType, float);
	void tick(const float);
	FPowerupType getType();
	bool isAlive();
	
private:
	FPowerupType m_type;
	float m_time;
};

#endif
