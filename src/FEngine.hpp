#ifndef __FENGINE_HPP__
#define __FENGINE_HPP__

#include <vector>

#include "FDirection.hpp"
#include "FObject.hpp"
#include "FCharacter.hpp"
#include "FWeapon.hpp"
#include "FVector.hpp"
#include "FLevel.hpp"
#include "FPowerup.hpp"
#include "FProjectile.hpp"

class FEngine
{
public:
	FEngine(std::shared_ptr<FLevel>);
	
	void addPlayer(FCharacter);
	std::shared_ptr<FLevel> getLevel();
		
	void tick(float);
	bool isRunning();
	
	void print();
	int getTickCount();
	
	void createProjectile();
	void createPowerup();
	void createEffect();
	
private:
	void clean();

	std::vector<FCharacter> m_characters;
	std::vector<FProjectile> m_projectiles;
	std::vector<FPowerup> m_powerups;
	std::shared_ptr<FLevel> m_level;
	int m_ticks;
	float m_time;
};

#endif