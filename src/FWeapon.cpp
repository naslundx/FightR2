#include "FWeapon.hpp"

FWeapon::FWeapon(float ammo, float maxAmmo, float cost, float maxCoolDown, FProjectileType projectileType, FWeaponType type)
: FObject(false, false, false, false)
{
	m_ammo = ammo;
	m_maxAmmo = maxAmmo;
	m_cost = cost;
	m_projectileType = projectileType;
	m_type = type;
	m_coolDownMax = maxCoolDown;
	m_coolDown = 0.f;
	m_fired = false;
}
	
bool FWeapon::canFire()
{
	return (m_ammo > m_cost && m_coolDown <= 0.f);
}

bool FWeapon::hasFired()
{
	auto result = m_fired;
	m_fired = false;
	return result;
}

void FWeapon::fire()
{
	if (canFire())
	{
		m_ammo -= m_cost;
		m_fired = true;
		m_coolDown = m_coolDownMax;
	}
}
	
void FWeapon::tick(const float delta)
{
	if (m_coolDown > 0.f)
	{
		m_coolDown -= delta;
	}
	else
	{
		m_coolDown = 0.f;
		if (m_ammo < m_maxAmmo)
		{
			m_ammo += delta;
		}
		else
		{
			m_ammo = m_maxAmmo;
		}
	}
}

void FWeapon::reload()
{
	m_ammo = m_maxAmmo;
}

FWeaponType FWeapon::getType()
{
	return m_type;
}

FProjectileType FWeapon::getProjectileType()
{
	return m_projectileType;
}
