#pragma once
#include "glm\vec3.hpp"

class BoundingBox {
public:
	glm::vec3 center;
	float hWidth, hHeight, hDepth;

	bool intersect(const BoundingBox* subject) const;
	bool intersect(glm::vec3 corner, float sides) const;


	BoundingBox(glm::vec3 centerPoint, float sides);
	BoundingBox();
	~BoundingBox();
};