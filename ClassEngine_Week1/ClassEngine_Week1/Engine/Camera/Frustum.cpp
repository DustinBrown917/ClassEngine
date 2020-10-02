#include "Frustum.h"
#include "Camera.h"


Frustum::Frustum() : camera(nullptr)
{

}

Frustum::Frustum(Camera* camera_)
{
	camera = camera_;

	nearDimensions = glm::vec2();
	farDimensions = glm::vec2();

}

Frustum::~Frustum()
{
	
}

void Frustum::UpdateFrustum()
{
	nearDimensions.y = tan(camera->GetFOV() * 0.5f) * camera->GetClippingPlanes().x * 2.0F;
	nearDimensions.x = nearDimensions.y * camera->GetAspect();

	farDimensions.y = tan(camera->GetFOV() * 0.5f) * camera->GetClippingPlanes().y * 2.0f;
	farDimensions.x = farDimensions.y * camera->GetAspect();

	BuildPlanes();
}

void Frustum::BuildPlanes()
{
	planes[NEAR] = Plane(camera->GetForward(), camera->GetPosition() + (camera->GetForward() * camera->GetClippingPlanes().x));
	planes[FAR] = Plane(camera->GetForward() * -1.0f, camera->GetPosition() + (camera->GetForward() * camera->GetClippingPlanes().y));

	//A line drawn in the plane at the edge of the view frustum
	glm::vec3 planeLine = glm::vec3();

	//Right plane
	//Find a point at the very edge of the view frustum on the side we want to make a plane for.
	//Remove the position of the camera and that point becomes a direction.
	planeLine = (planes[NEAR].point + (camera->GetRight() * (nearDimensions.x * 0.5f))) - camera->GetPosition();

	//Normalize it to make it a unit direction.
	planeLine = glm::normalize(planeLine);

	//Cross Camera.up with the planeLine and we get a perpindicular normal.
	planes[RIGHT] = Plane(glm::cross(camera->GetUp(), planeLine), camera->GetPosition());

	

	//Left plane
	planeLine = (planes[NEAR].point + camera->GetRight() * (nearDimensions.x * -0.5f)) - camera->GetPosition();
	planeLine = glm::normalize(planeLine);
	planes[LEFT] = Plane(glm::cross(-camera->GetUp(), planeLine), camera->GetPosition());

	

	//Bottom plane
	//Swap Up and Right from above to flip the plane on it's side.
	planeLine = (planes[NEAR].point - camera->GetUp() * (nearDimensions.y * 0.5f)) - camera->GetPosition();
	planeLine = glm::normalize(planeLine);
	planes[BOTTOM] = Plane(glm::cross(camera->GetRight(), planeLine), camera->GetPosition());

	

	//Top plane
	planeLine = (planes[NEAR].point - camera->GetUp() * (nearDimensions.y * -0.5f)) - camera->GetPosition();
	planeLine = glm::normalize(planeLine);
	planes[TOP] = Plane(glm::cross(-camera->GetRight(), planeLine), camera->GetPosition());
}

bool Frustum::IsPointInside(glm::vec3 point_) {

	for (Plane p : planes) {
		if (p.DistanceToPoint(point_) < 0) {
			return false;
		}
	}
	return true;
}

void Frustum::OnDestroy()
{
	camera = nullptr;
}


