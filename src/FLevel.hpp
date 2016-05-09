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
	void loadFromFile(const std::string);
	FTile get(const int, const int);
	void set(const int, const int, const FTile);	
	
	int getWidth();
	int getHeight();
	int getTileSize();
	
private:
	int m_width, m_height, m_tileSize;
	FTile* m_data;
};

#endif
