#include "FCharacter.hpp"

FCharacter::FCharacter(std::vector<FWeapon> weapons, std::string name, int team, bool ai)
: FObject(true, true, true)
{
	m_weapons = weapons;
	m_name = name;
	m_team = team;
	m_ai = ai;
}

FCharacter::FCharacter(FVector position, FVector velocity, std::vector<FWeapon> weapons, std::string name, int team, bool ai)
: FObject(position, velocity, true, true, true)
{
	m_weapons = weapons;
	m_name = name;
	m_team = team;
	m_ai = ai;
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
	//TODO
}

void FCharacter::jump()
{
	//TODO	
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
}

void FCharacter::tick(float delta)
{
	FObject::tick(delta);
}
