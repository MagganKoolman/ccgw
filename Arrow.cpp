#include "Arrow.h"

void Arrow::update(Input* input) {
	
}

Arrow::Arrow(int travelSpeed, glm::vec3 downVector) {
	this->mSpeed = travelSpeed;
	this->mGravitation = downVector;
}
Arrow::~Arrow() {

}
