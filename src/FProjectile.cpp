#include "FProjectile.hpp"

FProjectile::FProjectile(FVector position, FVector size, int type, float time = FLT_MAX)
: FObject(position, size, true, true, true)
{
	m_type = type;
	m_time = time;
}

void FProjectile::tick(float delta)
{
	m_time -= delta;
}

int FProjectile::getType()
{
	return m_type;
}

bool FProjectile::isAlive()
{
	return (m_time > 0.f);
}
