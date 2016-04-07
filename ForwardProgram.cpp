#include "ForwardProgram.h"

ForwardProgram::ForwardProgram(){

}

ForwardProgram::ForwardProgram(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath) : ShaderProgram() {
	compileShaders(vertexPath, fragmentPath, geometryPath);
}

ForwardProgram::~ForwardProgram() {

}

void ForwardProgram::use() {
	glUseProgram(mProgramID);
	for (int i = 0; i < mTotalAttributes; i++)
	{
		glEnableVertexAttribArray(i);
	}
	glBindFramebuffer(GL_FRAMEBUFFER,0);
	glViewport(0, 0, 1080, 720);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ForwardProgram::unUse() {
	glUseProgram(0);
	for (int i = 0; i < mTotalAttributes; i++)
	{
		glDisableVertexAttribArray(i);
	}
}