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
			it->move(FDirection::left);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			it->move(FDirection::right);
			
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			it->move(FDirection::up);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			it->move(FDirection::down);
	}
}

void FGame::render()
{
	m_window->clear();
		
	// Render all tiles
	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			auto data = m_engine->getLevel()->get(x, y);
			auto sprite = loadSprite(m_tileMap[data], m_tileSize, m_tileSize);
			sprite->setPosition(sf::Vector2f(x * m_tileSize, y * m_tileSize));
			m_window->draw(*sprite);
		}
	}
			
	// Render characters and their weapons
	for (auto &character : m_engine->getCharacters())
	{
		if (character.getHealth() > 0)
		{
			auto sprite = loadSprite(m_characterTypeMap[character.getType()], character.getSize().x, character.getSize().y);
			sprite->setPosition(sf::Vector2f(character.getPosition().x, character.getPosition().y));
			m_window->draw(*sprite);
			
			// auto weapon = character.getWeapon();
			// auto weaponSprite = loadSprite(m_weaponTypeMap[weapon.getType()], weapon.getSize().x, weapon.getSize().y);
			// weaponSprite->setPosition(sf::Vector2f(character.getPosition().x + character.getSize().x / 2.f, character.getPosition().y + character.getSize().y / 2.f));
			// m_window->draw(*weaponSprite);
		}
	}
	
	// Render projectiles
	for (auto &projectile : m_engine->getProjectiles())
	{
		auto sprite = loadSprite(m_projectileTypeMap[projectile.getType()], projectile.getSize().x, projectile.getSize().y);
		sprite->setPosition(sf::Vector2f(projectile.getPosition().x, projectile.getPosition().y));
		m_window->draw(*sprite);
	}
	
	// Render powerups
	for (auto &powerup : m_engine->getPowerups())
	{
		auto sprite = loadSprite(m_powerupTypeMap[powerup.getType()], powerup.getSize().x, powerup.getSize().y);
		sprite->setPosition(sf::Vector2f(powerup.getPosition().x, powerup.getPosition().y));
		m_window->draw(*sprite);
	}
	
	// Render effects
	//TODO

	m_window->display();
}

void FGame::setTile(FTile typeName, std::string filename)
{
	m_tileMap[typeName] = filename;
}

void FGame::setCharacterType(FCharacterType typeName, std::string filename)
{
	m_characterTypeMap[typeName] = filename;	
}

void FGame::setWeaponType(FWeaponType typeName, std::string filename)
{
	m_weaponTypeMap[typeName] = filename;	
}

void FGame::setProjectileType(FProjectileType typeName, std::string filename)
{
	m_projectileTypeMap[typeName] = filename;	
}

void FGame::setPowerupType(FPowerupType typeName, std::string filename)
{
	m_powerupTypeMap[typeName] = filename;	
}
