#include "FWeapon.hpp"

FWeapon::FWeapon(int ammo, int maxAmmo, int cost, int load, FProjectileType projectileType, FWeaponType type)
: FObject(false, false, false, false)
{
	m_ammo = ammo;
	m_maxAmmo = maxAmmo;
	m_cost = cost;
	m_load = load;
	m_projectileType = projectileType;
	m_type = type;
	m_fired = false;
}
	
bool FWeapon::canFire()
{
	return (m_ammo > m_cost);
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
	}
}
	
void FWeapon::tick(float delta)
{
	if (m_ammo < m_maxAmmo)
	{
		m_ammo += m_load;
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
