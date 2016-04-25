#include "FCharacter.hpp"

FCharacter::FCharacter(std::vector<FWeapon> weapons, std::string name, int team, bool ai, FCharacterType type, int health, int lives)
: FObject(true, true, true)
{
	m_weapons = weapons;
	m_name = name;
	m_team = team;
	m_ai = ai;
	m_jumpCounter = 0;
	m_type = type;
	m_health = health;
	m_lives = lives;
}

FCharacter::FCharacter(FVector position, FVector velocity, std::vector<FWeapon> weapons, std::string name, int team, bool ai, FCharacterType type, int health, int lives)
: FObject(position, velocity, true, true, true)
{
	m_weapons = weapons;
	m_name = name;
	m_team = team;
	m_ai = ai;
	m_jumpCounter = 0;
	m_type = type;
	m_health = health;
	m_lives = lives;
}

int FCharacter::getLives()
{
	return m_lives;
}

void FCharacter::setLives(int lives)
{
	m_lives = lives;
}

int FCharacter::getHealth()
{
	return m_health;
}

void FCharacter::heal(int health)
{
	m_health += health;
	if (m_health > m_maxHealth)
		m_health = m_maxHealth;
}

void FCharacter::hurt(int health)
{
	m_health -= health;
	if (m_health < 0)
	{
		m_health = 0;
		--m_lives;
	}
}

void FCharacter::resurrect()
{
	if (m_lives > 0)
	{
		m_health = m_maxHealth;
	}
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

FCharacterType FCharacter::getType()
{
	return m_type;
}

void FCharacter::move(FDirection direction)
{
	FVector acceleration;
	switch (direction)
	{
		case up:
			//TODO Add ladders
			jump();
			break;
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
	if (m_jumpCounter == 0 && fabs(m_velocity.y) < 0.1f )
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
	if (m_jumpCounter > 0)
	{
		--m_jumpCounter;
		FVector jumpVector(0.f, -0.2f);
		accelerate(jumpVector);		
	}

	if (m_ai)
	{
		updateAI();
	}
	
	FObject::tick(delta);
}
