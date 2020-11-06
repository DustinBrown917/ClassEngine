#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include <string>
#include <glew.h>
#include <vector>
#include "Particle.h"

class ParticleEmitter 
{
public:
	ParticleEmitter(int numToEmit_, std::string shaderProgram_);
	void Update(const float deltaTime_);
	void Render(Camera* camera);

	glm::vec3 position;

private:
	int numToEmit;
	GLuint shaderProgram;

	std::vector<Particle*> particles;

	void RandomizeValues(Particle* p);

	float RandomRange(float min, float max);

};

#endif // !PARTICLEEMITTER_H



