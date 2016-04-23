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
	//TODO
	return true;
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
		
		for (float x = position.x; x <= position.x + size.x; x += tileSize)
		{
			if (tileIsSolid(m_level->get(x / tileSize, position.y / tileSize)))
			{
				// std::cout << "top";
				position.y += (tileSize - fmod(position.y, tileSize));
				character.land();
				break;
			}
			if (tileIsSolid(m_level->get(x / tileSize, (position.y + size.y) / tileSize)))
			{
				// std::cout << "bottom";
				position.y -= fmod(position.y, tileSize) - 0.1f;
				character.land();
				break;
			}
		}
		
		for (float y = position.y; y < position.y + size.y; y += tileSize)
		{
			if (tileIsSolid(m_level->get(position.x / tileSize, y / tileSize)))
			{
				// std::cout << "left";
				position.x += (tileSize - fmod(position.x, tileSize));
				character.halt();
				break;
			}
			if (tileIsSolid(m_level->get((position.x + size.x) / tileSize, y / tileSize)))
			{
				// std::cout << "right";
				position.x -= fmod(position.x, tileSize);
				character.halt();
				break;
			}
		}
		character.setPosition(position);
	}
	
	// Projectile&Character
	//TODO
	
	// Projectile&Wall
	//TODO
	
	// Powerup&Character
	//TODO
	
	// Powerup&Wall
	//TODO
}

bool FEngine::tileIsSolid(char tile)
{
	return tile == 'a';	
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
