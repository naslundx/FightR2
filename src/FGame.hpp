#ifndef __FGAME_HPP__
#define __FGAME_HPP__

#include <SFML/Graphics.hpp>

#include "FObject.hpp"
#include "FEngine.hpp"
#include "FGame.hpp"

class FGame
{
public:
	FGame(std::shared_ptr<FEngine>);
	
	void run();	
private:
	std::unique_ptr<sf::RenderWindow> m_window;
	std::shared_ptr<FEngine> m_engine;
	
	int m_width, m_height, m_tileSize;
};

#endif
