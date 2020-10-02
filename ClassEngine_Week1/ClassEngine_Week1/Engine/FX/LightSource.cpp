#include "LightSource.h"

LightSource::LightSource(glm::vec3 position_, float ambientValue_, float diffuseValue_, glm::vec3 colour_)
{
	position = position_;
	ambientValue = ambientValue_;
	diffuseValue = diffuseValue_;
	colour = colour_;
}

LightSource::~LightSource()
{
}

void LightSource::SetPosition(const glm::vec3 position_)
{
	position = position_;
}

void LightSource::SetAmbientValue(const float ambientValue_)
{
	ambientValue = ambientValue_;
}

void LightSource::SetDiffuseValue(const float diffuseValue_)
{
	diffuseValue = diffuseValue;
}

void LightSource::SetColour(const glm::vec3 colour_)
{
	colour = colour_;
}

glm::vec3 LightSource::GetPosition() const
{
	return position;
}

float LightSource::GetAmbientValue() const
{
	return ambientValue;
}

float LightSource::GetDiffuseValue() const
{
	return diffuseValue;
}

glm::vec3 LightSource::GetColour() const
{
	return colour;
}
