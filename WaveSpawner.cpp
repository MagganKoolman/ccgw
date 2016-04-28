#include "WaveSpawner.h"

void WaveSpawner::update( float deltaTime )
{
	mDelay -= deltaTime;

	if( mDelay <= 0.0f )
	{
		if( mCurMoleratmen < mSpawnMoleratmen )
		{
			spawnMoleratman();
		}

		if( mCurMolebats < mSpawnMolebats )
		{
			spawnMolebat();
		}

		mDelay = WAVESPAWNER_DELAY;
	}
}

void WaveSpawner::spawn()
{
	mCurMoleratmen = 0;
	mCurMolebats = 0;

	mDelay = 0.0f;

	// TODO: Do something useful here
	mSpawnMoleratmen = 0;
	mSpawnMolebats = pGameData->mMolebats;
}

void WaveSpawner::incrementWave()
{
	mWave++;
}

void WaveSpawner::setPosition( glm::vec3 position )
{
	mPosition = position;
}

glm::vec3 WaveSpawner::getPosition() const
{
	return mPosition;
}

void WaveSpawner::spawnMoleratman()
{
	Moleratman* m = nullptr;

	for( int i=0; i<pGameData->mMoleratmen && m == nullptr; i++ )
		if( !pGameData->pMoleratmen[i].getAlive() )
			m = &pGameData->pMoleratmen[i];

	if( m )
	{
		m->setPosition( mPosition );
		m->setAlive( true );
	}
}

void WaveSpawner::spawnMolebat()
{
	Molebat* m = nullptr;

	for( int i=0; i<pGameData->mMolebats && m == nullptr; i++ )
		if( !pGameData->pMolebats[i].getAlive() )
			m = &pGameData->pMolebats[i];

	if( m )
	{
		glm::vec3 pos = mPosition;
		pos.y = MOLEBAT_HEIGHT;
		m->setPosition( pos );
		m->setAlive( true );
	}
}

WaveSpawner& WaveSpawner::operator=( const WaveSpawner& ref )
{
	mWave = ref.mWave;
	mDelay = ref.mDelay;
	mPosition = ref.mPosition;

	mCurMoleratmen = ref.mCurMoleratmen;
	mSpawnMoleratmen = ref.mSpawnMoleratmen;
	mCurMolebats = ref.mCurMolebats;
	mSpawnMolebats = ref.mSpawnMolebats;

	// TODO: This shouldn't be necessary
	pGameData = ref.pGameData;

	return *this;
}

WaveSpawner::WaveSpawner( const WaveSpawner& ref )
	: pGameData( ref.pGameData ),
	mWave( ref.mWave ), mDelay( ref.mDelay ), mPosition( ref.mPosition ),
	mCurMoleratmen( ref.mCurMoleratmen ), mSpawnMoleratmen( ref.mSpawnMoleratmen ),
	mCurMolebats( ref.mCurMolebats ), mSpawnMolebats( ref.mSpawnMolebats )
{
}

WaveSpawner::WaveSpawner( GameData* data )
	: pGameData( data ),
	mWave( 1 ), mDelay( 0.0f ), mPosition( 0.0f ),
	mCurMoleratmen( 0 ), mSpawnMoleratmen( 0 ),
	mCurMolebats( 0 ), mSpawnMolebats( 0 )
{
}

WaveSpawner::~WaveSpawner()
{
}