#include "FEngine.hpp"

FEngine::FEngine(std::shared_ptr<FLevel> level)
{
	m_level = level;
	m_ticks = 0;
}

void FEngine::addPlayer(FCharacter player)
{
	m_characters.push_back(player);
}

std::shared_ptr<FLevel> FEngine::getLevel()
{
	return m_level;
}
	
void FEngine::tick(float delta)
{	
	for (auto &character : m_characters)
	{
		character.tick(delta);
	}
	for (auto &projectile : m_projectiles)
	{
		projectile.tick(delta);
	}
	for (auto &powerup : m_powerups)
	{
		powerup.tick(delta);
	}

	collisionDetection();	
	++m_ticks;
	m_time += delta;
}

bool FEngine::isRunning()
{
	std::vector<int> teams;
	for (auto character : m_characters)
		if (character.isAlive())
			teams.push_back(character.getTeam());
	for (int i=0; i<teams.size()-1; i++)
		for (int j=1; j<teams.size(); j++)
			if (teams[i] != teams[j])
				return true;
	return false;
}

void FEngine::print()
{
	//TODO
}

int FEngine::getTickCount()
{
	return m_ticks;
}

float FEngine::getTime()
{
	return m_time;
}

void FEngine::createProjectile()
{
	//TODO
}

void FEngine::createPowerup()
{
	//TODO
}

void FEngine::createEffect()
{
	//TODO
}

void FEngine::clean()
{
	//TODO
}

void FEngine::collisionDetection()
{
	auto tileSize = m_level->getTileSize();
	
	// Character&Wall
	for (auto &character : m_characters)
	{
		auto position = character.getPosition(), size = character.getSize();
		if (position.clampTo(0.f, 0.f, m_level->getWidth() * tileSize - size.x, m_level->getHeight() * tileSize - size.y))
		 	character.land();

		character.setPosition(position);
		
		if (collisionLeft(character) || collisionRight(character))
			character.halt();
			
		if (collisionUp(character) || collisionDown(character))
			character.land();
	}
	
	// Projectile&Character
	//TODO
	
	// Projectile&Wall
	for (auto &projectile : m_projectiles)
	{
		auto position = projectile.getPosition(), size = projectile.getSize();
		if (position.clampTo(0.f, 0.f, m_level->getWidth() * tileSize - size.x, m_level->getHeight() * tileSize - size.y))
		 	projectile.land();

		projectile.setPosition(position);
		
		if (collisionLeft(projectile) || collisionRight(projectile))
			projectile.halt();
			
		if (collisionUp(projectile) || collisionDown(projectile))
			projectile.land();
	}
	
	// Powerup&Character
	//TODO
	
	// Powerup&Wall
	for (auto &powerup : m_powerups)
	{
		auto position = powerup.getPosition(), size = powerup.getSize();
		if (position.clampTo(0.f, 0.f, m_level->getWidth() * tileSize - size.x, m_level->getHeight() * tileSize - size.y))
		 	powerup.land();

		powerup.setPosition(position);
		
		if (collisionLeft(powerup) || collisionRight(powerup))
			powerup.halt();
			
		if (collisionUp(powerup) || collisionDown(powerup))
			powerup.land();
	}
}

bool FEngine::collisionUp(FObject& object)
{
	auto tileSize = m_level->getTileSize();
	auto position = object.getPosition(), size = object.getSize(); 
	for (float x = position.x; x <= position.x + size.x; x += tileSize)
	{
		if (tileIsSolid(m_level->get(x / tileSize, position.y / tileSize)))
		{
			position.y += (tileSize - fmod(position.y, tileSize));
			object.setPosition(position);
			return true;
		}
	}
	return false;
}

bool FEngine::collisionDown(FObject& object)
{
	auto tileSize = m_level->getTileSize();
	auto position = object.getPosition(), size = object.getSize(); 
	for (float x = position.x; x <= position.x + size.x; x += tileSize)
	{
		if (tileIsSolid(m_level->get(x / tileSize, (position.y + size.y) / tileSize)))
		{
			position.y -= fmod(position.y, tileSize) - 0.1f;
			object.setPosition(position);
			return true;
		}
	}
	return false;
}

bool FEngine::collisionLeft(FObject& object)
{
	auto tileSize = m_level->getTileSize();
	auto position = object.getPosition(), size = object.getSize();
	for (float y = position.y; y < position.y + size.y; y += tileSize)
	{
		if (tileIsSolid(m_level->get(position.x / tileSize, y / tileSize)))
		{
			position.x += (tileSize - fmod(position.x, tileSize));
			object.setPosition(position);
			return true;
		}
	}
	return false;
}

bool FEngine::collisionRight(FObject& object)
{
	auto tileSize = m_level->getTileSize();
	auto position = object.getPosition(), size = object.getSize();
	for (float y = position.y; y < position.y + size.y; y += tileSize)
	{
		if (tileIsSolid(m_level->get((position.x + size.x) / tileSize, y / tileSize)))
		{
			position.x -= fmod(position.x, tileSize);
			object.setPosition(position);
			return true;
		}
	}
	return false;
}

std::vector<FCharacter>& FEngine::getCharacters()
{
	return m_characters;
}

std::vector<FProjectile>& FEngine::getProjectiles()
{
	return m_projectiles;
}

std::vector<FPowerup>& FEngine::getPowerups()
{
	return m_powerups;
}
