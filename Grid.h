#pragma once

enum
{
	TILE_EMPTY = 0,
	TILE_BOX = 0x1,
	TILE_BALLISTA = 0x2,
};

//Grid class used to hold information about the gameboard.
class Grid
{
public:
	//Determines if a tile has a/several specific flag/flags.
	bool tileIs( int x, int y, char flags ) const;

	//Set a tile to a/several specific flag/flags.
	void setTile( int x, int y, char flags );
	//Returns the flags of a tile.
	char getTile( int x, int y ) const;

	//Returns the entire grid.
	char* getGrid() const;
	//Returns the width of the grid.
	int getWidth() const;
	//Returns the height of the grid.
	int getHeight() const;

	Grid( int width, int height );
	~Grid();

private:
	int mWidth, mHeight;
	char* mpGrid;
};