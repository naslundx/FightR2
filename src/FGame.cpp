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
	
	// Map types to filenames
	//TODO This should be done externally through a method in this class
	m_characterTypeMap[FCharacterType::DEBUG] = "images/business.png";	
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
	
	while (m_window->isOpen() && m_engine->isRunning())
	{
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
	auto &characters = m_engine->getCharacters();
	auto it = std::find_if(characters.begin(), characters.end(), [] (FCharacter& character) { return character.isHuman(); } );
	if (it != characters.end())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			std::cout << "moving left";
			it->move(FDirection::left);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			std::cout << "moving right";
			it->move(FDirection::right);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			std::cout << "moving up";
			it->move(FDirection::up);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			std::cout << "moving down";
			it->move(FDirection::down);
		}
	}
}

void FGame::render()
{
	m_window->clear();
		
	// Render all tiles
	for (int y = 0; y < m_height; y++)
		for (int x = 0; x < m_width; x++) {
			std::shared_ptr<sf::Sprite> sprite;
			char data = m_engine->getLevel()->get(x, y);
			switch (data)
			{
				case 'a':
					sprite = loadSprite("images/Metalplates.png", 10, 10);
					break;
				default:
					sprite = loadSprite("images/Sandstone.png", 10, 10);
			}
			sf::Vector2f position(x * m_tileSize, y * m_tileSize);
			sprite->setPosition(position);
			m_window->draw(*sprite);
		}
			
	// Render characters
	for (auto &character : m_engine->getCharacters())
	{
		auto sprite = loadSprite(m_characterTypeMap[character.getType()], character.getSize().x, character.getSize().y);
		sprite->setPosition(sf::Vector2f(character.getPosition().x, character.getPosition().y));
		m_window->draw(*sprite);
	}
	
	// Render weapons
	//TODO
	
	// Render projectiles
	//TODO
	
	// Render effects
	//TODO

	m_window->display();
}
