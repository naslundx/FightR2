#include "FGame.hpp"

//Images were downloaded from opengameart.org

FGame::FGame(std::shared_ptr<FEngine> engine)
{
	m_engine = engine;
	auto level = engine->getLevel();
	
	m_width = level->getWidth();
	m_height = level->getHeight();
	m_tileSize = level->getTileSize();
	
	sf::RenderWindow *window = new sf::RenderWindow(
		sf::VideoMode(m_width * m_tileSize, m_height * m_tileSize),
		"FightR 2.0"
	);
	m_window = std::unique_ptr<sf::RenderWindow>(window);		
}

// TODO: Find a way to keep textures not destroyed
//sf::Sprite FGame::loadSprite(std::string fileName)
//{
//	sf::Texture texture;
//	if (!texture.loadFromFile(fileName, sf::IntRect(0, 0, m_tileSize, m_tileSize)))
//	{
//		std::cout << "ERROR in texture loading at " << __LINE__ << " in File" << __FILE__ << std::endl;
//	}
//	sf::Sprite sprite;
//	sprite.setTexture(texture);
//	return sprite;
//}
	
void FGame::run()
{
	// Load textures and sprites
	sf::Texture texture1, texture2;
	if (!texture1.loadFromFile("images/Sandstone.png", sf::IntRect(0, 0, m_tileSize, m_tileSize)))
	{
		std::cout << "ERROR in texture1 loading at " << __LINE__ << " in File " << __FILE__ << std::endl;
	}
	if (!texture2.loadFromFile("images/Metalplates.png", sf::IntRect(0, 0, m_tileSize, m_tileSize)))
	{
		std::cout << "ERROR in texture2 loading at " << __LINE__ << " in File " << __FILE__ << std::endl;
	}
	sf::Sprite sprite1, sprite2;
	sprite1.setTexture(texture1);
	sprite2.setTexture(texture2);

	//sprite1 = loadSprite("images/Sandstone.png");
	//sprite2 = loadSprite("images/Metalplates.png");

	while (m_window->isOpen() && m_engine->isRunning() && m_engine->getTickCount() < 100)
	{
		std::cout << m_engine->getTickCount() << std::endl;
		
		// Update
		m_engine->tick(0.f);
		m_engine->print();
		
		// Render
		m_window->clear();
		
		//...render all tiles
		for (int y = 0; y < m_height; y++)
			for (int x = 0; x < m_width; x++) {
				char data = m_engine->getLevel()->get(x, y);
				if(data == 'a')
				{
					sprite2.setPosition(sf::Vector2f(x * m_tileSize, y * m_tileSize));
					m_window->draw(sprite2);
				}
				else
				{
					sprite1.setPosition(sf::Vector2f(x * m_tileSize, y * m_tileSize));
					m_window->draw(sprite1);
				}
			}
		
		m_window->display();
		
		// Check any keyboard inputs
		sf::Event event;
		while (m_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window->close();
		}
	}
}
