#ifndef __FWEAPON_HPP__
#define __FWEAPON_HPP__

#include "FDirection.hpp"
#include "FObject.hpp"
#include "FTypes.hpp"

class FWeapon: public FObject
{
public:
	FWeapon(int, int, int, int, FProjectileType, FWeaponType);
	
	bool hasFired();
	bool canFire();
	void fire();
	void tick(float);
	void reload();
	FWeaponType getType();
	FProjectileType getProjectileType();
	
private:
	bool m_fired;
	int m_ammo, m_maxAmmo, m_cost, m_load;
	FProjectileType m_projectileType;
	FWeaponType m_type;
};

#endif
