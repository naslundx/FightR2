#include "FWeapon.hpp"

FWeapon::FWeapon(int ammo, int maxAmmo, int cost, int load, int projectileID, FWeaponType type)
: FObject(false, false, false)
{
	m_ammo = ammo;
	m_maxAmmo = maxAmmo;
	m_cost = cost;
	m_load = load;
	m_projectileID = projectileID;
	m_type = type;
}
	
bool FWeapon::canFire()
{
	return (m_ammo > m_cost);
}
	
void FWeapon::fire(FDirection)
{
	if (canFire())
	{
		m_ammo -= m_cost;
		//m_game->createProjectile();
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