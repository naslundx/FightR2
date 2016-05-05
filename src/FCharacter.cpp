#include "FCharacter.hpp"

FCharacter::FCharacter(std::vector<FWeapon> weapons, std::string name, int team, bool ai, FCharacterType type, int health, int lives)
: FObject(true, true, true, true)
{
	m_weapons = weapons;
	m_name = name;
	m_team = team;
	m_ai = ai;
	m_jumpCounter = 0;
	m_type = type;
	m_health = health;
	m_maxHealth = health;
	m_lives = lives;
	m_currentWeapon = 0;
	m_facingLeft = false;
	m_resurrect = 0.f;
}

FCharacter::FCharacter(FVector position, FVector velocity, std::vector<FWeapon> weapons, std::string name, int team, bool ai, FCharacterType type, int health, int lives)
: FObject(position, velocity, true, true, true, true)
{
	m_weapons = weapons;
	m_name = name;
	m_team = team;
	m_ai = ai;
	m_jumpCounter = 0;
	m_type = type;
	m_health = health;
	m_maxHealth = health;
	m_lives = lives;
	m_currentWeapon = 0;
	m_facingLeft = false;
	m_resurrect = 0.f;
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

int FCharacter::getMaxHealth()
{
	return m_maxHealth;
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
	if (m_health <= 0)
	{
		kill();
	}
}

void FCharacter::kill()
{
	m_health = 0;
	--m_lives;
	m_resurrect = 3.f;
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
	const float speed = 0.23f;
	FVector acceleration;
	switch (direction)
	{
		case up:
			if (m_ladder)
				acceleration = FVector(0.f, -speed);
			else
				jump();
			break;
		case down:
			if (m_ladder)
				acceleration = FVector(0.f, speed);
			break;
		case left:
			m_facingLeft = true;
			acceleration = FVector(-speed, 0.f);
			break;
		case right:
			m_facingLeft = false;
			acceleration = FVector(speed, 0.f);
			break;
	}
	accelerate(acceleration);
}

void FCharacter::jump()
{
	if (m_standing && m_jumpCounter == 0.f && fabs(m_velocity.y) < 0.1f)
	{
		m_jumpCounter = 0.4f;
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

bool FCharacter::facingLeft()
{
	return m_facingLeft;
}

void FCharacter::fire()
{
	m_weapons[m_currentWeapon].fire();
}

void FCharacter::setWeaponIndex(int index)
{
	while (index < 0)
		index += m_weapons.size();
	m_currentWeapon = index % m_weapons.size();
}

void FCharacter::updateAI()
{
	//TODO
	move(FDirection::left); // just do something
}

void FCharacter::tick(float delta)
{
	if (getHealth() > 0)
	{
		if (m_jumpCounter > 0.f)
		{
			m_jumpCounter -= delta;
			FVector jumpVector(0.f, -0.4f);
			accelerate(jumpVector);		
		}
		else
		{
			m_jumpCounter = 0.f;
		}

		if (m_ai)
		{
			updateAI();
		}

		for (auto &weapon : m_weapons)
			weapon.tick(delta);
			
		setGravitational(!m_ladder);
		
		FObject::tick(delta);
	}
	else
	{
		m_resurrect -= delta;
		if (m_resurrect < 0.f)
		{
			resurrect();
		}
	}
}
