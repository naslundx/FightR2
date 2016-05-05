#include "FLevel.hpp"

FLevel::FLevel()
{
	m_width = 0;
	m_height = 0;
	m_data = nullptr;
}

FLevel::FLevel(int width, int height, int tilesize)
{
	m_width = width;
	m_height = height;
	m_tileSize = tilesize;
	m_data = new FTile[m_width * m_height];
}

FLevel::~FLevel()
{
	delete[] m_data;
}

void FLevel::clear()
{
	for (int y = 0; y < m_height; ++y)
		for (int x = 0; x < m_width; ++x)
			set(x, y, FTile::DEBUG_BLANK);
}

void FLevel::randomize()
{
	clear();
	//TODO
	for (int x = m_width / 2 - 10; x < m_width / 2 + 10; ++x)
		set(x, m_height / 2, FTile::DEBUG_SOLID);
		
	for (int y = 2; y < m_height - 6; ++y)
		set(12, y, FTile::DEBUG_LADDER);
}

void FLevel::loadFromFile(std::string path)
{
	//TODO	
}

FTile FLevel::get(int x, int y)
{
	return m_data[y * m_width + x];
}

void FLevel::set(int x, int y, FTile data)
{
	m_data[y * m_width + x] = data;
}

int FLevel::getWidth()
{
	return m_width;
}

int FLevel::getHeight()
{
	return m_height;
}

int FLevel::getTileSize()
{
	return m_tileSize;
}
