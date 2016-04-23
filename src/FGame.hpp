#ifndef __FGAME_HPP__
#define __FGAME_HPP__

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <algorithm>

#include "FObject.hpp"
#include "FEngine.hpp"
#include "FGame.hpp"
#include "FTypes.hpp"

class FGame
{
public:
	FGame(std::shared_ptr<FEngine>);
	
	void run();
	void setTile(FTile, std::string);
	void setCharacterType(FCharacterType, std::string);
	void setWeaponType(FWeaponType, std::string);
	void setProjectileType(FProjectileType, std::string);
	void setPowerupType(FPowerupType, std::string);

private:
	std::shared_ptr<sf::Sprite> loadSprite(std::string fileName, int width, int height);
	void processEvents();
	void render();

	// For rendering
	int m_width, m_height, m_tileSize;
	std::unique_ptr<sf::RenderWindow> m_window;
	std::shared_ptr<FEngine> m_engine;
	std::unordered_map<std::string, std::shared_ptr<sf::Sprite>> m_sprites;
	std::unordered_map<std::string, std::shared_ptr<sf::Texture>> m_textures;
	
	// Map types to filenames
	std::map<FTile, std::string> m_tileMap;
	std::map<FCharacterType, std::string> m_characterTypeMap;
	std::map<FWeaponType, std::string> m_weaponTypeMap;
	std::map<FPowerupType, std::string> m_powerupTypeMap;
	std::map<FProjectileType, std::string> m_projectileTypeMap;
};

#endif
