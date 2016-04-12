#pragma once

#include <GL\glew.h>

/*We only ever need one of these.*/
class Billboard
{
public:
	/*Allocates memory on the GPU.*/
	void alloc();
	/*Deallocates memory on the GPU.*/
	void dealloc();
	/*Draws the billboard.*/
	void draw();

	Billboard& operator=( const Billboard& ref );
	Billboard( const Billboard& ref );
	Billboard();
	~Billboard();

private:
	GLuint mVertexArray;
};