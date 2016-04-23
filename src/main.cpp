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
	//TODO Add weapons
	std::string nameone = "Marcus";
	std::string nametwo = "Computer";
	FCharacter one(FVector(250.f, 150.f), FVector(20.f, 40.f), std::vector<FWeapon>(), nameone, 1, false, FCharacterType::DEBUG);
	FCharacter two(FVector(450.f, 350.f), FVector(20.f, 40.f), std::vector<FWeapon>(), nameone, 2, true, FCharacterType::DEBUG);
	engine->addPlayer(one);
	engine->addPlayer(two);
	
	// Create the game and run the main loop
	FGame game(engine);
	game.setCharacterType(FCharacterType::DEBUG, "images/business.png");
	game.run();

	return 0;
}