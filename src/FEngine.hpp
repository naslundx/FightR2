#ifndef __FENGINE_HPP__
#define __FENGINE_HPP__

#include <vector>
#include <random>

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
	std::vector<FCharacter>& getCharacters();
	std::vector<FProjectile>& getProjectiles();
	std::vector<FPowerup>& getPowerups();
		
	void tick(float);
	bool isRunning();
	
	void print();
	int getTickCount();
	float getTime();
	
	void createProjectile(FProjectile);
	void createPowerup();
	void createEffect();
	
private:
	void clean();
	void collisionDetection();
	bool collisionLeft(FObject&);
	bool collisionRight(FObject&);
	bool collisionUp(FObject&);
	bool collisionDown(FObject&);
	bool touchingLadder(FObject&);
	FVector findEmptySpace(FVector&);

	std::vector<FCharacter> m_characters;
	std::vector<FProjectile> m_projectiles;
	std::vector<FPowerup> m_powerups;
	std::shared_ptr<FLevel> m_level;
	int m_ticks;
	float m_time;
};

#endif
