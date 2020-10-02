#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <glew.h>
#include <glm/glm.hpp>

class LightSource
{

public:

	LightSource(glm::vec3 position_, float ambientValue_, float diffuseValue_, glm::vec3 colour_);
	~LightSource();

	void SetPosition(const glm::vec3 position_);
	void SetAmbientValue(const float ambientValue_);
	void SetDiffuseValue(const float diffuseValue_);
	void SetColour(const glm::vec3 colour_);

	glm::vec3 GetPosition() const;
	float GetAmbientValue() const;
	float GetDiffuseValue() const;
	glm::vec3 GetColour() const;



private:
	glm::vec3 position;
	float ambientValue;
	float diffuseValue;
	glm::vec3 colour;
};
#endif // !LIGHTSOURCE_H


