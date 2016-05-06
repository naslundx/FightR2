#ifndef __FCHARACTER_HPP__
#define __FCHARACTER_HPP__

#include <vector>
#include <cmath>

#include "FDirection.hpp"
#include "FObject.hpp"
#include "FWeapon.hpp"
#include "FTypes.hpp"
#include "FLevel.hpp"
#include "FPowerup.hpp"
#include "FProjectile.hpp"

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
	int getMaxHealth();
	void heal(int);
	void hurt(int);
	void kill();
	void resurrect();
	
	FCharacterType getType();
	void updateAI(std::vector<FCharacter>*, std::vector<FProjectile>*, std::vector<FPowerup>*);
	void tick(float);
	
	bool m_standing;
	bool m_ladder;

private:
	

	bool m_ai, m_facingLeft;
	float m_jumpCounter, m_resurrect;
	int m_currentWeapon, m_team, m_health, m_maxHealth, m_lives;
	std::vector<FWeapon> m_weapons;
	std::string m_name;
	FCharacterType m_type;
	
};

#endif
