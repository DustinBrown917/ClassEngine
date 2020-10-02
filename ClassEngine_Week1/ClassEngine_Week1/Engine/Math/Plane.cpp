#include "Plane.h"

Plane::Plane() : normal(glm::vec3(0.0f, 1.0f, 0.0f)), point(glm::vec3())
{
}

Plane::Plane(glm::vec3 normal_, glm::vec3 point_)
{
	normal = normal_;
	point = point_;

	if (normal.length() != 1.0f) {
		normal = glm::normalize(normal);
	}
}

Plane::~Plane()
{
}

float Plane::DistanceToPoint(glm::vec3 target_)
{
	return glm::dot(normal, (target_ - point));
}
