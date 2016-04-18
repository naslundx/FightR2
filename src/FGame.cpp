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

std::shared_ptr<sf::Sprite> FGame::loadSprite(std::string fileName, int width, int height)
{
	auto exists = m_sprites.find(fileName);
	if (exists == m_sprites.end())
	{
		auto texture = std::make_shared<sf::Texture>();
		if (!texture->loadFromFile(fileName, sf::IntRect(0, 0, width, height)))
		{
			std::cout << "ERROR trying to load " << fileName;
		}
		auto sprite = std::make_shared<sf::Sprite>();
		sprite->setTexture(*texture);
		m_sprites[fileName] = sprite;
		m_textures[fileName] = texture;
		return sprite;
	}
	else
	{
		return exists->second;
	}	
}
	
void FGame::run()
{
	sf::Clock clock;
	sf::Time accumulator = sf::Time::Zero;
	sf::Time ups = sf::seconds(1.f / 60.f);
	
	while (m_window->isOpen() && m_engine->isRunning() && m_engine->getTickCount() < 100)
	{
		std::cout << m_engine->getTickCount() << ", " << m_engine->getTime() << std::endl;

		processEvents();
		
		while (accumulator > ups)
		{
			accumulator -= ups;
			m_engine->tick(ups.asSeconds());
			m_engine->print();
		}
		
		render();
		accumulator += clock.restart();	
	}
}

void FGame::processEvents()
{
	// Check events
	sf::Event event;
	while (m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window->close();
	}
	
	// Check keyboard press
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		//TODO
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		//TODO
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		//TODO
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		//TODO
	}
}

void FGame::render()
{
	// Load sprites
	auto sprite1 = loadSprite("images/Sandstone.png", 10, 10);
	auto sprite2 = loadSprite("images/Metalplates.png", 10, 10);
	
	// Clear
	m_window->clear();
		
	// Render all tiles
	for (int y = 0; y < m_height; y++)
			for (int x = 0; x < m_width; x++) {
				sf::Vector2f position(x * m_tileSize, y * m_tileSize);
				char data = m_engine->getLevel()->get(x, y);
				if(data == 'a')
				{
					sprite2->setPosition(position);
					m_window->draw(*sprite2);
				}
				else
				{
					sprite1->setPosition(position);
					m_window->draw(*sprite1);
				}
			}
		
	m_window->display();
}
