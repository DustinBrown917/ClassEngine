#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "../FX/LightSource.h"
#include "Frustum.h"

class Camera
{
public:
	Camera();
	~Camera();

	void SetPosition(glm::vec3 position_);
	void SetRotation(float yaw_, float pitch_);

	glm::mat4 GetView() const;
	glm::mat4 GetPerspective() const;
	glm::mat4 GetOrthographic() const;
	glm::vec2 GetClippingPlanes() const;
	float GetFOV() const;
	float GetAspect() const;
	glm::vec3 GetForward() const;
	glm::vec3 GetUp() const;
	glm::vec3 GetRight() const;

	bool IsInFrustum(glm::vec3 point_);

	void AddLightSource(LightSource* lightSource_);
	std::vector<LightSource*> GetLightSources();
	glm::vec3 GetPosition() const;
	void OnDestroy();

	void ProcessMouseMovement(glm::vec2 offset_);
	void ProcessMouseZoom(int y_);

	void SetMouseLook(const bool enabled);

private:
	glm::vec3 position;
	glm::mat4 perspective, orthographic;
	float fov;
	float yaw, pitch;
	float nearPlane, farPlane;
	bool mouseLook;
	glm::vec3 forward, up, right, worldUp;
	Frustum frustum;

	void UpdateCameraVector();
	void ReCalcPersp();
	void ReCalcOrtho();

	std::vector<LightSource*> lightSources;
};

#endif // !CAMERA_H


