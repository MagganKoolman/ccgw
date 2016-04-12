#include "Billboard.h"

void Billboard::alloc()
{
	glGenVertexArrays( 1, &mVertexArray );
	glBindVertexArray( mVertexArray );

	glEnableVertexAttribArray( 0 );

	const GLfloat vdata[] = { 0.0f, 0.0f, 0.0f };
	const GLuint idata = 0;

	GLuint vbo, ibo;
	glGenBuffers( 1, &vbo );
	glBindBuffer( GL_ARRAY_BUFFER, vbo );
	glBufferData( GL_ARRAY_BUFFER, sizeof(GLfloat)*3, vdata, GL_STATIC_DRAW );

	glGenBuffers( 1, &ibo );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ibo );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint), &idata, GL_STATIC_DRAW );

	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );

	glBindVertexArray( 0 );
}

void Billboard::dealloc()
{
	glDeleteVertexArrays( 1, &mVertexArray );
}

void Billboard::draw()
{
	glBindVertexArray( mVertexArray );
	glDrawElements( GL_TRIANGLES, 1, GL_UNSIGNED_INT, 0 );
	glBindVertexArray( 0 );
}

Billboard& Billboard::operator=( const Billboard& ref )
{
	mVertexArray = ref.mVertexArray;
	return *this;
}

Billboard::Billboard( const Billboard& ref )
	: mVertexArray( ref.mVertexArray )
{
}

Billboard::Billboard()
	: mVertexArray( 0 )
{
}

Billboard::~Billboard()
{
}