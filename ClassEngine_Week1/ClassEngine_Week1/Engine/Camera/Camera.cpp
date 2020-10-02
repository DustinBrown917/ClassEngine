#include "Camera.h"

#include "../Core/CoreEngine.h"

Camera::Camera() : position(glm::vec3())
{
	fov = 45.0f;
	forward = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	worldUp = up;
	nearPlane = 2.0f;
	farPlane = 50.0f;
	yaw = -90.0f;
	pitch = 0.0f;

	frustum = Frustum(this);

	ReCalcOrtho();
	ReCalcPersp();

	UpdateCameraVector();
}

Camera::~Camera()
{
}

void Camera::SetPosition(glm::vec3 position_)
{
	position = position_;
	UpdateCameraVector();
}

void Camera::SetRotation(float yaw_, float pitch_)
{
	yaw = yaw_;
	pitch = pitch_;
	UpdateCameraVector();
}

glm::mat4 Camera::GetView() const
{
	return glm::lookAt(position, position + forward, up);
}

glm::mat4 Camera::GetPerspective() const
{

	return perspective;
}

glm::mat4 Camera::GetOrthographic() const
{
	return orthographic;
}

glm::vec2 Camera::GetClippingPlanes() const
{
	return glm::vec2(nearPlane, farPlane);
}

float Camera::GetFOV() const
{
	return fov;
}

float Camera::GetAspect() const
{
	glm::vec2 dim = CoreEngine::GetInstance()->GetWindowSize();
	
	return (float)dim.x / (float)dim.y;
}

glm::vec3 Camera::GetForward() const
{
	return forward;
}

glm::vec3 Camera::GetUp() const
{
	return up;
}

glm::vec3 Camera::GetRight() const
{
	return right;
}

bool Camera::IsInFrustum(glm::vec3 point_)
{
	return frustum.IsPointInside(point_);
}

void Camera::AddLightSource(LightSource* lightSource_)
{
	lightSources.push_back(lightSource_);
}

std::vector<LightSource*> Camera::GetLightSources()
{
	return lightSources;
}

glm::vec3 Camera::GetPosition() const
{
	return position;
}

void Camera::OnDestroy()
{

	for (auto ls : lightSources) {
		delete ls;
		ls = nullptr;
	}
	lightSources.clear();

}

void Camera::ProcessMouseMovement(glm::vec2 offset_)
{
	offset_ *= 0.15f;

	yaw += offset_.x;
	pitch += offset_.y;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	else if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	if (yaw > 360.0f) {
		yaw -= 360.0f;
	}
	else if (yaw < 0.0f) {
		yaw += 360.0f;
	}

	UpdateCameraVector();
}

void Camera::ProcessMouseZoom(int y_)
{
	if (y_ < 0 || y_ > 0) {
		position += static_cast<float>(y_)* (forward * 2.0f);
	}

	UpdateCameraVector();
}

void Camera::UpdateCameraVector()
{
	forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward.y = sin(glm::radians(pitch));
	forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	forward = glm::normalize(forward);

	right = glm::normalize(glm::cross(forward, worldUp));

	up = glm::normalize(glm::cross(right, forward));

	frustum.UpdateFrustum();
}

void Camera::ReCalcPersp()
{
	perspective = glm::perspective(fov, CoreEngine::GetInstance()->GetWindowSize().x / CoreEngine::GetInstance()->GetWindowSize().y, nearPlane, farPlane);
}

void Camera::ReCalcOrtho()
{
	orthographic = glm::ortho(0.0f, CoreEngine::GetInstance()->GetWindowSize().x, 0.0f, CoreEngine::GetInstance()->GetWindowSize().y, -1.0f, 1.0f);
}
