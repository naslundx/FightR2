#ifndef __FCHARACTER_HPP__
#define __FCHARACTER_HPP__

#include <vector>

#include "FDirection.hpp"
#include "FCharacter.hpp"
#include "FObject.hpp"
#include "FWeapon.hpp"

class FCharacter: public FObject
{
public:
	FCharacter(std::vector<FWeapon>, std::string, int, bool);
	FCharacter(FVector, FVector, std::vector<FWeapon>, std::string, int, bool);
	
	int getTeam();
	void setTeam(int);
	bool isHuman();
	void move(FDirection);
	void jump();
	
	FWeapon& getWeapon();
	int getWeaponIndex();
	void fire(FDirection);
	void setWeaponIndex(int);
	
	void updateAI();
	void tick(float);
	
private:
	bool m_ai;
	int m_currentWeapon, m_team, m_jumpCounter;
	std::vector<FWeapon> m_weapons;
	std::string m_name;
};

#endif
