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
