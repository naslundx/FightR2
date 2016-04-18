#ifndef __FWEAPON_HPP__
#define __FWEAPON_HPP__

#include "FDirection.hpp"
#include "FObject.hpp"

class FWeapon: public FObject
{
public:
	FWeapon(int, int, int, int, int);
	
	bool canFire();
	void fire(FDirection);
	void tick(float);
	void reload();
	
private:
	int m_ammo, m_maxAmmo, m_cost, m_load, m_projectileID;
};

#endif
