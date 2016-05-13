#include "FEffect.hpp"

FEffect::FEffect(FVector position, FVector size, FEffectType type, float time = FLT_MAX)
: FObject(position, size, false, true, false, false)
{
	m_type = type;
	m_time = time;
}

void FEffect::tick(float delta)
{
	m_time -= delta;
	FObject::tick(delta);
}

FEffectType FEffect::getType()
{
	return m_type;
}

bool FEffect::isAlive()
{
	return (m_time > 0.f);
}
