#ifndef PARTICLE_H
#define PARTICLE_H

#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Camera/Camera.h"

struct ParticleVertex {
	glm::vec3 position;
	glm::vec3 colour;
};

class Particle
{
public:
	Particle();
	Particle(GLuint shaderProgram);
	~Particle();

	void Render(Camera* camera);

	void SetVelocity(glm::vec3 v);
	glm::vec3 GetVelocity();

	void SetPosition(glm::vec3 v);
	glm::vec3 GetPosition();

	void SetColour(glm::vec3 v);
	glm::vec3 GetColour();

	void SetLifeTime(float f);
	float GetLifeTime();

	void SetSize(float f);
	float GetSize();

private:
	void GenerateBuffers();

	glm::vec3 velocity;

	ParticleVertex vert;

	float lifeTime;
	float size;

	GLuint VAO;
	GLuint shaderProgram;
	GLuint viewMatLoc, projMatLoc, sizeLoc, colourLoc, posLoc;
};
#endif


