#include "FGame.hpp"

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
	
void FGame::run()
{
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
				sf::RectangleShape tile(sf::Vector2f(10.f, 10.f));
   				tile.setFillColor(sf::Color::Black);
				tile.setPosition(x * m_tileSize, y * m_tileSize);
				char data = m_engine->getLevel()->get(x, y);
				if (data == 'a')
					tile.setFillColor(sf::Color::Red);
				m_window->draw(tile);
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
