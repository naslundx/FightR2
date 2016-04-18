#include "FPowerup.hpp"

FPowerup::FPowerup(FVector position, FVector size, int type, float time = FLT_MAX)
: FObject(position, size, true, true, true)
{
	m_type = type;
	m_time = time;
}

void FPowerup::tick(float delta)
{
	m_time -= delta;
}

int FPowerup::getType()
{
	return m_type;
}

bool FPowerup::isAlive()
{
	return (m_time > 0.f);
}
