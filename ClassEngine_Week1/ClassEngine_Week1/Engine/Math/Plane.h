
#ifndef PLANE_H
#define PLANE_H

#include <glm/glm.hpp>

struct Plane
{
	glm::vec3 normal, point;

	Plane();
	Plane(glm::vec3 normal_, glm::vec3 point_);
	~Plane();

	float DistanceToPoint(glm::vec3 target_);
};
#endif // !PLANE_H


