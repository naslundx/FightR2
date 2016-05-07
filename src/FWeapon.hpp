#ifndef __FWEAPON_HPP__
#define __FWEAPON_HPP__

#include "FDirection.hpp"
#include "FObject.hpp"
#include "FTypes.hpp"

class FWeapon: public FObject
{
public:
	FWeapon(float, float, float, float, FProjectileType, FWeaponType);
	
	bool hasFired();
	bool canFire();
	void fire();
	void tick(const float);
	void reload();
	FWeaponType getType();
	FProjectileType getProjectileType();
	
private:
	bool m_fired;
	float m_ammo, m_maxAmmo, m_cost, m_coolDown, m_coolDownMax;
	FProjectileType m_projectileType;
	FWeaponType m_type;
};

#endif
