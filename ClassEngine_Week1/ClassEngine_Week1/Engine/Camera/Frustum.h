#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "../Math/Plane.h"

class Camera;

class Frustum
{
public:
	Frustum(Camera* camera_);
	Frustum();
	~Frustum();

	void UpdateFrustum();
	bool IsPointInside(glm::vec3 point_);
	void OnDestroy();

private:
	
	enum {
		NEAR,
		FAR,
		TOP,
		BOTTOM,
		LEFT,
		RIGHT
	};
	Plane planes[6];
	glm::vec2 nearDimensions, farDimensions;
	Camera* camera;

	void BuildPlanes();
};


#endif // !FRUSTUM_H


