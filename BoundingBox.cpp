#include "BoundingBox.h"
#include <math.h>


bool BoundingBox::intersect(const BoundingBox* subject) const {
	return !(
						(fabsf(this->center.x - subject->center.x)	>	this->hWidth + subject->hWidth)
			||			(fabsf(this->center.y - subject->center.y)	>	this->hHeight + subject->hHeight)
			||			(fabsf(this->center.z - subject->center.z)	>	this->hDepth + subject->hDepth)
		);
}
bool BoundingBox::intersect(glm::vec3 acenter, float halfSide) const {
	bool result = !(
						(fabsf(this->center.x - acenter.x)	>	this->hWidth  +	 halfSide)
					||	(fabsf(this->center.y - acenter.y)	>	this->hHeight +	 halfSide)
					||	(fabsf(this->center.z - acenter.z)	>	this->hDepth  +	 halfSide)
		);
	return result;
}

BoundingBox::BoundingBox(glm::vec3 centerPoint, float sides) {
	this->center = centerPoint;
	this->hDepth = sides/2;
	this->hHeight = sides/2;
	this->hWidth = sides/2;
}
BoundingBox::BoundingBox() {

}
BoundingBox::~BoundingBox() {

}