#include "FCharacter.hpp"

FCharacter::FCharacter(std::vector<FWeapon> weapons, std::string name, int team, bool ai)
: FObject(true, true, true)
{
	m_weapons = weapons;
	m_name = name;
	m_team = team;
	m_ai = ai;
	m_jumpCounter = 0;
}

FCharacter::FCharacter(FVector position, FVector velocity, std::vector<FWeapon> weapons, std::string name, int team, bool ai)
: FObject(position, velocity, true, true, true)
{
	m_weapons = weapons;
	m_name = name;
	m_team = team;
	m_ai = ai;
	m_jumpCounter = 0;
}

int FCharacter::getTeam()
{
	return m_team;
}

void FCharacter::setTeam(int team)
{
	m_team = team;
}

bool FCharacter::isHuman()
{
	return !m_ai;
}

void FCharacter::move(FDirection direction)
{
	FVector acceleration;
	switch (direction)
	{
		case up:
		case down:
			//TODO Add ladders
			break;
		case left:
			acceleration = FVector(-0.09f, 0.f);
			break;
		case right:
			acceleration = FVector(0.09f, 0.f);
			break;
	}
	accelerate(acceleration);
}

void FCharacter::jump()
{
	if (m_jumpCounter == 0)
	{
		m_jumpCounter = 15;	// jump for 15 frames
	}
}

FWeapon& FCharacter::getWeapon()
{
	return m_weapons[m_currentWeapon];
}

int FCharacter::getWeaponIndex()
{
	return m_currentWeapon;
}

void FCharacter::fire(FDirection direction)
{
	m_weapons[m_currentWeapon].fire(direction);
}

void FCharacter::setWeaponIndex(int index)
{
	m_currentWeapon = index % m_weapons.size();
}

void FCharacter::updateAI()
{
	//TODO
	move(FDirection::left); // just do something
}

void FCharacter::tick(float delta)
{
	if (m_jumpCounter-- > 0)
	{
		FVector jumpVector(0.f, -1.f);
		accelerate(jumpVector);		
	}
	
	FObject::tick(delta);
	
	std::cout << "\nPos=" << this->m_position << "\nVel=" << this->m_velocity << "\n";
}
