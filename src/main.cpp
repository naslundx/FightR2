#include <iostream>
#include <string>
#include <memory>

#include "FGame.hpp"
#include "FLevel.hpp"
#include "FEngine.hpp"
#include "FCharacter.hpp"
#include "FWeapon.hpp"
#include "FVector.hpp"
#include "FObject.hpp"
#include "FTypes.hpp"
#include "FTile.hpp"

int main(int argc, char** argv)
{
	// Create level
	const int WIDTH = 64;
	const int HEIGHT = 48;
	const int TILESIZE = 10;
	auto level = std::make_shared<FLevel>(WIDTH, HEIGHT, TILESIZE);
	level->randomize();
	auto engine = std::make_shared<FEngine>(level);
	
	// Create characters
	std::string nameone = "Marcus";
	std::string nametwo = "Computer";
	FCharacter one(
		FVector(250.f, 150.f),
		FVector(20.f, 40.f),
		std::vector<FWeapon> { FWeapon(10.f, 10.f, 2.f, 1.f, FProjectileType::DEBUG, FWeaponType::DEBUG) },
		nameone,
		1,
		false,
		FCharacterType::DEBUG,
		100,
		3
	);
	FCharacter two(
		FVector(450.f, 350.f),
		FVector(20.f, 40.f), // float ammo, float maxAmmo, float cost, float maxCoolDown
		std::vector<FWeapon> { FWeapon(10.f, 10.f, 2.f, 1.f, FProjectileType::DEBUG, FWeaponType::DEBUG) },
		nameone,
		2,
		true,
		FCharacterType::DEBUG,
		100,
		3
	);
	engine->addPlayer(one);
	engine->addPlayer(two);
	
	// Create the game and run the main loop
	FGame game(engine);
	game.setCharacterType(FCharacterType::DEBUG, "images/business.png");
	game.setWeaponType(FWeaponType::DEBUG, "images/Sandstone.png");
	game.setProjectileType(FProjectileType::DEBUG, "images/bug.png");
	game.setTile(FTile::DEBUG_BLANK, "images/Sandstone.png");
	game.setTile(FTile::DEBUG_SOLID, "images/Metalplates.png");
	game.run();

	return 0;
}
