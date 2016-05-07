#ifndef __FEFFECT_HPP__
#define __FEFFECT_HPP__

#include <float.h>

#include "FObject.hpp"
#include "FTypes.hpp"

class FEffect : public FObject
{
public:
	FEffect(FVector, FVector, FEffectType, float);
	void tick(float);
	FEffectType getType();
	bool isAlive();
	
private:
	FEffectType m_type;
	float m_time;
};

#endif
