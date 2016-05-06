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
		character.updateAI(&m_characters, &m_projectiles, &m_powerups);
		
		if (character.getHealth() > 0)
		{
			auto &weapon = character.getWeapon();
			if (weapon.hasFired())
			{
				// TODO: Move to createProjectile()
				FVector position, velocity;
				if (character.facingLeft())
				{
					position = FVector(-character.getSize().x * 0.5f, character.getSize().y / 2.f) + character.getPosition();
					velocity = FVector(character.getVelocity().x - 1.f, 0.f);
				}
				else
				{
					position = FVector(character.getSize().x * 1.5f, character.getSize().y / 2.f) + character.getPosition();
					velocity = FVector(character.getVelocity().x + 1.f, 0.f);
				}
				auto projectile = FProjectile(position, FVector(10, 10), weapon.getProjectileType(), 1000.f, false, false);
				projectile.setVelocity(velocity);
				createProjectile(projectile);
			}
		}
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
	
	for (auto &character : m_characters)
	{
		if (character.getHealth() <= 0.f)
		{
			// TODO: This only has to happen once per death
			character.setPosition(findEmptySpace(character.getSize()));
		}
	}
	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> randomvalue(0, 1);
	if (randomvalue(gen) < 0.005f)
		createPowerup();
	
	clean();	
	++m_ticks;
	m_time += delta;
}

bool FEngine::isRunning()
{
	std::vector<int> teams;
	for (auto character : m_characters)
		if (character.getLives() > 0)
			teams.push_back(character.getTeam());
	for (auto first = teams.begin(); first != teams.end() - 1; ++first)
		for (auto second = first + 1; second != teams.end(); ++second)
			if (*first != *second)
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

void FEngine::createProjectile(FProjectile projectile)
{
	m_projectiles.push_back(projectile);
}

void FEngine::createPowerup()
{
	FVector size(25.f, 25.f);
	FVector position = findEmptySpace(size);
	FPowerup powerup(position, size, FPowerupType::DEBUG, 10.f);
	m_powerups.push_back(powerup);
}

void FEngine::createEffect()
{
	//TODO
}

void FEngine::clean()
{
	for (auto it = m_powerups.begin(); m_powerups.size() > 0 && it != m_powerups.end(); ++it)
	{
		if (!it->isAlive())
		{
			it = m_powerups.erase(it);
		}
	}
}

void FEngine::collisionDetection()
{
	auto tileSize = m_level->getTileSize();
	
	// Character&Wall
	for (auto &character : m_characters)
	{
		auto position = character.getPosition(), size = character.getSize();
		if (position.clampTo(0.f, -10.f, m_level->getWidth() * tileSize - size.x, m_level->getHeight() * tileSize))
		 	character.halt();
		
		if (position.clampTo(0.f, 0.f, m_level->getWidth() * tileSize - size.x, m_level->getHeight() * tileSize - size.y))
		 	character.land();

		character.m_standing = false;
		character.setPosition(position);
		
		if (collisionUp(character))
			character.land();
			
		if (collisionDown(character))
		{
			character.land();
			character.m_standing = true;
		}
			
		if (collisionLeft(character) || collisionRight(character))
			character.halt();
			
		character.m_standing = character.m_standing || position.y >= m_level->getHeight() * tileSize - size.y;
		character.m_ladder = touchingLadder(character);
	}
	
	// Projectile&Character
	for (auto it = m_projectiles.begin(); m_projectiles.size() > 0 && it != m_projectiles.end(); ++it)
	{
		for (auto &character : m_characters)
		{
			if (character.getHealth() > 0 && it->intersects(character))
			{
				it = m_projectiles.erase(it);
				character.hurt(10);
			}
		}
	}
	
	// Projectile&Wall
	for (auto it = m_projectiles.begin(); m_projectiles.size() > 0 && it != m_projectiles.end(); ++it)
	{
		auto projectile = *it;
		auto position = projectile.getPosition(), size = projectile.getSize();
		bool outside = position.clampTo(0.f, 0.f, m_level->getWidth() * tileSize - size.x, m_level->getHeight() * tileSize - size.y);

		if (outside || collisionLeft(projectile) || collisionRight(projectile) || collisionUp(projectile) || collisionDown(projectile))
			m_projectiles.erase(it);
	}
	
	// Powerup&Character
	for (auto &powerup : m_powerups)
	{
		for (auto &character : m_characters)
		{
			if (character.getHealth() > 0 && powerup.intersects(character))
			{
				//TODO
			}
		}
	}
	
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
			position.y -= fmod(position.y, tileSize) + 0.1f;
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

bool FEngine::touchingLadder(FObject& object)
{
	auto tileSize = m_level->getTileSize();
	auto position = object.getPosition(), size = object.getSize(); 
	for (float x = position.x; x <= position.x + size.x; x += tileSize)
	{
		for (float y = position.y; y <= position.y + size.y; y += tileSize)
		{
			if (tileIsLadder(m_level->get(x / tileSize, y / tileSize)))
			{
				return true;
			}
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

FVector FEngine::findEmptySpace(FVector& size)
{
	auto tileSize = m_level->getTileSize();
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> x(0, m_level->getWidth() * tileSize - size.x);
	std::uniform_real_distribution<> y(0, m_level->getHeight() * tileSize - size.y);
	bool result;
	
	while (true)
	{
		FVector position(x(gen), y(gen));
		result = true;
		
		for (float x = position.x; result && x <= position.x + size.x; x += tileSize)
		{
			for (float y = position.y; result && y <= position.y + size.y; y += tileSize)
			{
				if (tileIsSolid(m_level->get(x / tileSize, y / tileSize)))
					result = false;
			}
		}
		
		if (result)
			return position;
	}
	return FVector();
}