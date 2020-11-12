#include "Particle.h"
#include <iostream>

Particle::Particle() : VAO(0), shaderProgram(0), lifeTime(1), size(1), projMatLoc(0), viewMatLoc(0), sizeLoc(0), colourLoc(0), posLoc(0)
{
}

Particle::Particle(GLuint shaderProgram) : VAO(0), lifeTime(1), size(1), projMatLoc(0), viewMatLoc(0), sizeLoc(0), colourLoc(0), posLoc(0)
{
	this->shaderProgram = shaderProgram;
	GenerateBuffers();
}

Particle::~Particle()
{
	glCreateVertexArrays(1, &VAO);
}

void Particle::Render(Camera* camera_)
{
	glUseProgram(shaderProgram);
	glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));

	glUniform1f(sizeLoc, size);
	glUniform3fv(colourLoc, 1, glm::value_ptr(vert.colour));
	glUniform3fv(posLoc, 1, glm::value_ptr(vert.position));	

	glBindVertexArray(VAO);
	
	glEnable(GL_PROGRAM_POINT_SIZE);

	if (camera_->IsInFrustum(vert.position)) {
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		//glPointSize(10.0f);
		glDrawArrays(GL_POINTS, 0, 1);		
	}

	glDisable(GL_PROGRAM_POINT_SIZE);

	glBindVertexArray(0);
}

void Particle::SetVelocity(glm::vec3 v)
{
	velocity = v;
}

glm::vec3 Particle::GetVelocity()
{

	return velocity;
}

void Particle::SetPosition(glm::vec3 v)
{
	vert.position = v;
}

glm::vec3 Particle::GetPosition()
{
	return vert.position;
}

void Particle::SetColour(glm::vec3 v)
{
	vert.colour = v;
}

glm::vec3 Particle::GetColour()
{
	return vert.colour;
}

void Particle::SetLifeTime(float f)
{
	lifeTime = f;
}

float Particle::GetLifeTime()
{
	return lifeTime;
}

void Particle::SetSize(float f)
{
	size = f;
}

float Particle::GetSize()
{
	return size;
}

void Particle::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);


	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	viewMatLoc = glGetUniformLocation(shaderProgram, "view");
	projMatLoc = glGetUniformLocation(shaderProgram, "proj");
	sizeLoc = glGetUniformLocation(shaderProgram, "size");
	colourLoc = glGetUniformLocation(shaderProgram, "colour");
	posLoc = glGetUniformLocation(shaderProgram, "position");
}
