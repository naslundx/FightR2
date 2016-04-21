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
	//std::string nametwo = "Lalala";
	FCharacter one(FVector(250.f, 150.f), FVector(20.f, 40.f), std::vector<FWeapon>(), nameone, 1, false, FCharacterType::DEBUG);
	//FCharacter two(std::vector<FWeapon>(), nametwo, 2, true);
	engine->addPlayer(one);
	//engine->addPlayer(two);
	
	// Create the game and run the main loop
	FGame game(engine);
	game.loadCharacterType(FCharacterType::DEBUG,
	"images/business.png"); // or all the available filenames should be saved as in string (without loading images) and just use FCharacterType?
	game.run();

	return 0;
}
