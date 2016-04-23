#ifndef __FLEVEL_HPP__
#define __FLEVEL_HPP__

#include <memory>
#include "FTile.hpp"

class FLevel
{
public:
	FLevel();
	FLevel(int, int, int);
	~FLevel();
	
	void clear();
	void randomize();
	void loadFromFile(std::string);
	FTile get(int, int);
	void set(int, int, FTile);	
	
	int getWidth();
	int getHeight();
	int getTileSize();
	
private:
	int m_width, m_height, m_tileSize;
	FTile* m_data;
};

#endif
