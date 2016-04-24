#ifndef __FCHARACTER_HPP__
#define __FCHARACTER_HPP__

#include <vector>
#include <cmath>

#include "FDirection.hpp"
#include "FCharacter.hpp"
#include "FObject.hpp"
#include "FWeapon.hpp"
#include "FTypes.hpp"

class FCharacter: public FObject
{
public:
	FCharacter(std::vector<FWeapon>, std::string, int, bool, FCharacterType);
	FCharacter(FVector, FVector, std::vector<FWeapon>, std::string, int, bool, FCharacterType);
	
	int getTeam();
	void setTeam(int);
	bool isHuman();
	void move(FDirection);
	void jump();
	bool isAlive();
	
	FWeapon& getWeapon();
	int getWeaponIndex();
	void fire(FDirection);
	void setWeaponIndex(int);
	
	FCharacterType getType();
	void updateAI();
	void tick(float);
	
private:
	bool m_ai;
	int m_currentWeapon, m_team, m_jumpCounter;
	std::vector<FWeapon> m_weapons;
	std::string m_name;
	FCharacterType m_type;
};

#endif
