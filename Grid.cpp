#include "Grid.h"

bool Grid::findPath( sNode start, sNode end, sNode* path, int* targets )
{
	bool result = false;

	std::vector<sNode*> openList;
	std::vector<sNode*> closedList;

	for( int i=0; i<mWidth*mHeight; i++ )
	{
		mGScore[i] = 999999;
		mFScore[i] = 999999;
		mPath[i].x = i%mWidth;
		mPath[i].y = i/mWidth;
		mPath[i].parent = nullptr;
		mPath[i].score = 0;
	}
	
	mGScore[NODEAT(start.x,start.y)] = 0;
	mFScore[NODEAT(start.x,start.y)] = heuristic( &start, &end );
	
	sNode* first = &mPath[NODEAT(start.x,start.y)];
	openList.push_back(first);

	while( openList.size() > 0 )
	{
		std::vector<sNode*>::iterator currentIT = openList.end();
		int currentScore = 999999;
		for( std::vector<sNode*>::iterator it = openList.begin(); it != openList.end(); it++ )
		{
			int score = mFScore[NODEAT((*it)->x,(*it)->y)];
			if( score < currentScore )
			{
				currentScore = score;
				currentIT = it;
			}
		}

		if( currentIT == openList.end() )
			throw -1;

		if( (*currentIT)->x == end.x && (*currentIT)->y == end.y )
		{
			// DONE
			sNode* parent = mPath[NODEAT((*currentIT)->x,(*currentIT)->y)].parent;
			int cur = 0;
			while( parent != nullptr )
			{
				path[cur++] = *parent;
				parent = parent->parent;
			}

			*targets = cur;
			break;
		}
		else
		{
			closedList.push_back(*currentIT);
			openList.erase( currentIT );
			currentIT = closedList.end()-1;

			if( (*currentIT)->x > 0 )
			{
				sNode* left = &mPath[NODEAT((*currentIT)->x-1, (*currentIT)->y)];
				left->score = heuristic( left, &end );
				left->parent = *currentIT;

				bool found = false;
				for( std::vector<sNode*>::iterator it = closedList.begin(); it != closedList.end() && !found; it++ )
				{
					if( (*it)->x == left->x && (*it)->y == left->y )
						found = true;
				}

				if( !found )
				{
					int tscore = mGScore[NODEAT((*currentIT)->x, (*currentIT)->y)] + 1;
					
					found = false;
					for( std::vector<sNode*>::iterator it = openList.begin(); it != openList.end() && !found; it++ )
					{
						if( (*it)->x == (*currentIT)->x && (*it)->y == (*currentIT)->y )
							found = true;
					}

					if( !found || tscore < mGScore[NODEAT(left->x, left->y)])
					{
						openList.push_back( left );

						mGScore[NODEAT(left->x,left->y)] = tscore;
						mFScore[NODEAT(left->x,left->y)] = mGScore[NODEAT(left->x,left->y)] + heuristic( left, &end );
					}
				}
			}
		}
	}

	return result;
}

bool Grid::tileIs( int x, int y, uchar flags ) const
{
	return ( ( getTile( x, y ) & flags ) > 0 );
}

void Grid::setTile( int x, int y, uchar flags )
{
	mpGrid[y*mWidth+x] = flags;
}

uchar Grid::getTile( int x, int y ) const
{
	return mpGrid[y*mWidth+x];
}

uchar* Grid::getGrid() const
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

uchar Grid::heuristic( sNode* start, sNode* end )
{
	int difx = end->x - start->x;
	int dify = end->y - start->y;
	return ( difx*difx + dify*dify );
}

Grid::Grid( int width, int height )
	: mWidth( width ), mHeight( height )
{
	mpGrid = new uchar[width*height];
	mGScore = new int[width*height];
	mFScore = new int[width*height];
	mPath = new sNode[width*height];
}

Grid::~Grid()
{
	delete[] mpGrid;
	delete[] mGScore;
	delete[] mFScore;
	delete[] mPath;
}