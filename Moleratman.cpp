#include "Moleratman.h"

Moleratman& Moleratman::operator=( const Moleratman& ref )
{
	Enemy::operator=( ref );
	return *this;
}

Moleratman::Moleratman( const Moleratman& ref )
	: Enemy( ref )
{
}

Moleratman::Moleratman()
{
}

Moleratman::~Moleratman()
{
}