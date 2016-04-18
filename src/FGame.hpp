#ifndef __FGAME_HPP__
#define __FGAME_HPP__

#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "FObject.hpp"
#include "FEngine.hpp"
#include "FGame.hpp"

class FGame
{
public:
	FGame(std::shared_ptr<FEngine>);
	
	void run();	
private:
	std::shared_ptr<sf::Sprite> loadSprite(std::string fileName, int width, int height);
	void processEvents();
	void render();

	std::unique_ptr<sf::RenderWindow> m_window;
	std::shared_ptr<FEngine> m_engine;
	int m_width, m_height, m_tileSize;
	std::unordered_map<std::string, std::shared_ptr<sf::Sprite>> m_sprites;
	std::unordered_map<std::string, std::shared_ptr<sf::Texture>> m_textures;
};

#endif
