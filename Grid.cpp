#include "Grid.h"

bool Grid::tileIs( int x, int y, char flags ) const
{
	return ( ( getTile( x, y ) & flags ) > 0 );
}

void Grid::setTile( int x, int y, char flags )
{
	mpGrid[y*mWidth+x] = flags;
}

char Grid::getTile( int x, int y ) const
{
	return mpGrid[y*mWidth+x];
}

char* Grid::getGrid() const
{
	return mpGrid;
}

int Grid::getWidth() const
{
	return mWidth;
}

int Grid::getHeight() const
{
	return mHeight;
}

Grid::Grid( int width, int height )
	: mWidth( width ), mHeight( height )
{
	mpGrid = new char[width*height];
}

Grid::~Grid()
{
	delete[] mpGrid;
}