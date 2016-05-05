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
	FCharacter(std::vector<FWeapon>, std::string, int, bool, FCharacterType, int, int);
	FCharacter(FVector, FVector, std::vector<FWeapon>, std::string, int, bool, FCharacterType, int, int);
	
	int getTeam();
	void setTeam(int);
	bool isHuman();
	void move(FDirection);
	void jump();
	bool facingLeft();
	
	FWeapon& getWeapon();
	int getWeaponIndex();
	void fire();
	void setWeaponIndex(int);
	
	int getLives();
	void setLives(int);
	int getHealth();
	void heal(int);
	void hurt(int);
	void resurrect();
	
	FCharacterType getType();
	void updateAI();
	void tick(float);
	
	bool m_standing;
	bool m_ladder;	
private:
	bool m_ai, m_facingLeft;
	float m_jumpCounter;
	int m_currentWeapon, m_team, m_health, m_maxHealth, m_lives;
	std::vector<FWeapon> m_weapons;
	std::string m_name;
	FCharacterType m_type;
};

#endif
