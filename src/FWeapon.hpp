#ifndef __FWEAPON_HPP__
#define __FWEAPON_HPP__

#include "FDirection.hpp"
#include "FObject.hpp"
#include "FTypes.hpp"

class FWeapon: public FObject
{
public:
	FWeapon(int, int, int, int, int, FWeaponType);
	
	bool canFire();
	void fire(FDirection);
	void tick(float);
	void reload();
	FWeaponType getType();
	
private:
	int m_ammo, m_maxAmmo, m_cost, m_load, m_projectileID;
	FWeaponType m_type;
};

#endif
