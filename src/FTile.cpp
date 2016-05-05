#include "FTile.hpp"

bool tileIsSolid(FTile tile)
{
	return tile == FTile::DEBUG_SOLID;	
}

bool tileIsLadder(FTile tile)
{
	return tile == FTile::DEBUG_LADDER;
}
