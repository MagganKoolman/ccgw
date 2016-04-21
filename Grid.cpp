#include "Grid.h"

bool Grid::findPath( sNode start, sNode end, sNode* path, int* targets )
{
	bool result = false;

	std::vector<sNode*> openList;
	std::vector<sNode*> closedList;
	std::vector<sNode*> accessList;

	for( int i=0; i<mWidth*mHeight; i++ )
	{
		mGScore[i] = 999999;
		mFScore[i] = 999999;
		mPath[i].x = i%mWidth;
		mPath[i].y = i/mWidth;
		mPath[i].parent = nullptr;
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
			// found a path
			sNode* parent = *currentIT;
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

			// TODO: Factor out into nicer code
			if( (*currentIT)->x > 0 ) // left
			{
				sNode* left = &mPath[NODEAT((*currentIT)->x-1, (*currentIT)->y)];

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
						left->parent = *currentIT;
						openList.push_back( left );

						mGScore[NODEAT(left->x,left->y)] = tscore;
						mFScore[NODEAT(left->x,left->y)] = tscore + heuristic( left, &end );
					}
				}
			}
			if( (*currentIT)->x < mWidth-1 ) // right
			{
				sNode* right = &mPath[NODEAT((*currentIT)->x+1, (*currentIT)->y)];

				bool found = false;
				for( std::vector<sNode*>::iterator it = closedList.begin(); it != closedList.end() && !found; it++ )
				{
					if( (*it)->x == right->x && (*it)->y == right->y )
						 found = true;
				}

				if( !found )
				{
					int tscore = mGScore[NODEAT((*currentIT)->x, (*currentIT)->y)] + 1;

					found = false;
					for( std::vector<sNode*>::iterator it = openList.begin(); it != openList.end() && !found; it++ )
					{
						if( (*it)->x == right->x && (*it)->y == right->y )
							found = true;
					}

					if( !found || tscore < mGScore[NODEAT(right->x, right->y)] )
					{
						right->parent = *currentIT;
						openList.push_back( right );

						mGScore[NODEAT(right->x, right->y)] = tscore;
						mFScore[NODEAT(right->x, right->y)] = tscore + heuristic( right, &end );
					}
				}
			}
			if( (*currentIT)->y > 0 ) // up
			{
				sNode* up = &mPath[NODEAT((*currentIT)->x, (*currentIT)->y-1)];

				bool found = false;
				for( std::vector<sNode*>::iterator it = closedList.begin(); it != closedList.end() && !found; it++ )
				{
					if( (*it)->x == up->x && (*it)->y == up->y )
						found = true;
				}

				if( !found )
				{
					int tscore = mGScore[NODEAT((*currentIT)->x, (*currentIT)->y)] + 1;

					found = false;
					for( std::vector<sNode*>::iterator it = openList.begin(); it != openList.end() && !found; it++ )
					{
						if( (*it)->x == up->x && (*it)->y == up->y )
							found = true;
					}

					if( !found  || tscore < mGScore[NODEAT(up->x, up->y)] )
					{
						up->parent = *currentIT;
						openList.push_back( up );

						mGScore[NODEAT( up->x, up->y )] = tscore;
						mFScore[NODEAT( up->x, up->y )] = tscore + heuristic( up, &end );
					}
				}
			}
			if( (*currentIT)->y < mHeight-1 ) // down
			{
				sNode* down = &mPath[NODEAT((*currentIT)->x, (*currentIT)->y + 1)];

				bool found = false;
				for (std::vector<sNode*>::iterator it = closedList.begin(); it != closedList.end() && !found; it++)
				{
					if ((*it)->x == down->x && (*it)->y == down->y)
						found = true;
				}

				if (!found)
				{
					int tscore = mGScore[NODEAT((*currentIT)->x, (*currentIT)->y)] + 1;

					found = false;
					for (std::vector<sNode*>::iterator it = openList.begin(); it != openList.end() && !found; it++)
					{
						if ((*it)->x == down->x && (*it)->y == down->y)
							found = true;
					}

					if (!found || tscore < mGScore[NODEAT(down->x, down->y)])
					{
						down->parent = *currentIT;
						openList.push_back(down);

						mGScore[NODEAT(down->x, down->y)] = tscore;
						mFScore[NODEAT(down->x, down->y)] = tscore + heuristic(down, &end);
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

Grid::Grid()
{

}

Grid::~Grid()
{
	delete[] mpGrid;
	delete[] mGScore;
	delete[] mFScore;
	delete[] mPath;
}