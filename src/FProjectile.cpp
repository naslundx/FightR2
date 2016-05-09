#include "FProjectile.hpp"

FProjectile::FProjectile(FVector position, FVector size, FProjectileType type, float time, bool gravity, bool drags)
: FObject(position, size, gravity, true, true, drags)
{
	m_type = type;
	m_time = time;
}

void FProjectile::tick(const float delta)
{
	m_time -= delta;
	FObject::tick(delta);
}

FProjectileType FProjectile::getType()
{
	return m_type;
}

bool FProjectile::isAlive()
{
	return (m_time > 0.f);
}
