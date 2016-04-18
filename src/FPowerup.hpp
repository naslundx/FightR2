#ifndef __FPOWERUP_HPP__
#define __FPOWERUP_HPP__

#include <float.h>

#include "FObject.hpp"

class FPowerup : public FObject
{
public:
	FPowerup(FVector, FVector, int, float);
	void tick(float);
	int getType();
	bool isAlive();
	
private:
	int m_type;
	float m_time;
};

#endif
