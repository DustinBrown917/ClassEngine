
#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include "../Camera/Camera.h"


struct Ray;
struct BoundingBox;

class CollisionDetection
{
public:
	CollisionDetection(const CollisionDetection&) = delete; //Disable copy constructor lvalue
	CollisionDetection(CollisionDetection&&) = delete; //Disable move constructor lvalue
	CollisionDetection& operator = (const CollisionDetection&) = delete; //Disable copy constructor rvalue
	CollisionDetection& operator = (CollisionDetection&&) = delete; //Disable move constructor rvalue

	CollisionDetection() = delete;
	~CollisionDetection();

	static Ray ScreenPosToWorldRay(glm::vec2 mouseCoords_, glm::vec2 screenSize_, Camera* camera_);
	static bool RayObbIntersection(Ray* ray_, BoundingBox* box_);

};


#endif // !COLLISIONDETECTION_H


