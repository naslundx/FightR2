#include "FPowerup.hpp"

FPowerup::FPowerup(FVector position, FVector size, FPowerupType type, float time = FLT_MAX)
: FObject(position, size, true, true, true, true)
{
	m_type = type;
	m_time = time;
}

void FPowerup::tick(const float delta)
{
	m_time -= delta;
	FObject::tick(delta);
}

FPowerupType FPowerup::getType()
{
	return m_type;
}

bool FPowerup::isAlive()
{
	return (m_time > 0.f);
}
