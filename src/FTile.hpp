#ifndef __FTILE_HPP__
#define __FTILE_HPP__

enum class FTile { 
	DEBUG_BLANK,
	DEBUG_SOLID,
	DEBUG_LADDER
};

bool tileIsSolid(FTile);
bool tileIsLadder(FTile);

#endif
