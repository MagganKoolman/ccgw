#include "Billboard.h"

void BillboardProgram::use()
{
	glUseProgram( mProgramID );


}

void BillboardProgram::unUse()
{
	glUseProgram( 0 );
}

void BillboardProgram::draw( Camera* camera, glm::vec3 position, glm::vec2 size )
{
	glDisable( GL_CULL_FACE );

	glm::mat4 world= glm::translate( glm::mat4(), position );
	GLuint worldLocation = glGetUniformLocation( mProgramID, "world" );
	glUniformMatrix4fv( worldLocation, 1, GL_FALSE, &world[0][0] );

	GLuint viewLocation = glGetUniformLocation( mProgramID, "view" );
	glUniformMatrix4fv( viewLocation, 1, GL_FALSE, &camera->getView()[0][0] );

	GLuint projectionLocation = glGetUniformLocation( mProgramID, "projection" );
	glUniformMatrix4fv( projectionLocation, 1, GL_FALSE, &camera->getPerspective()[0][0] );

	GLuint sizeLocation = glGetUniformLocation( mProgramID, "size" );
	glUniform2f( sizeLocation, size.x, size.y );

	glBindVertexArray(mVertexArray);

	glDrawElements(GL_POINTS, 1, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

BillboardProgram& BillboardProgram::operator=( const BillboardProgram& ref )
{
	throw -1;
}

BillboardProgram::BillboardProgram( const BillboardProgram& ref )
{
	throw -1;
}

BillboardProgram::BillboardProgram()
{
	throw -1;
}

BillboardProgram::BillboardProgram( const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath )
{
	compileShaders( vertexPath, fragmentPath, geometryPath );
	
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);

	glEnableVertexAttribArray(0);

	const GLfloat vdata[] = { 0.0f, 0.0f, 0.0f };
	const GLuint idata = 0;

	GLuint vbo, ibo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3, vdata, GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint), &idata, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

BillboardProgram::~BillboardProgram()
{
	glDeleteVertexArrays(1, &mVertexArray);
}