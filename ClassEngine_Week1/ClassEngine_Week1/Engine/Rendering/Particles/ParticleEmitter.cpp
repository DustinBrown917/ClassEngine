#include "ParticleEmitter.h"
#include "../../Graphics/ShaderHandler.h"


ParticleEmitter::ParticleEmitter(int numToEmit_, std::string shaderProgram_) : position(glm::vec3(0, 0, -10))
{
	numToEmit = numToEmit_;
	shaderProgram = ShaderHandler::GetInstance()->GetShader(shaderProgram_);

	if (shaderProgram == 0) {
		Debug::Error("Could not load shader " + shaderProgram, "ParticleEmitter.cpp", __LINE__);
		return;
	}

	particles = std::vector<Particle*>();
	particles.reserve(numToEmit);

	for (int i = 0; i < numToEmit; i++) {

		Particle* p = new Particle(shaderProgram);
		p->SetLifeTime(600.0f);
		p->SetColour(glm::vec3(1, 0, 0));
		RandomizeValues(p);
		p->SetPosition(p->GetPosition() + position);

		particles.push_back(p);
	}

}


void ParticleEmitter::Update(const float deltaTime_)
{ 
	for (int i = 0; i < particles.size(); i++) {
		particles[i]->SetLifeTime(particles[i]->GetLifeTime() - deltaTime_);
		particles[i]->SetPosition(particles[i]->GetPosition() + (particles[i]->GetVelocity() * deltaTime_));
		if (particles[i]->GetLifeTime() <= 0) {
			delete particles[i];
			particles.erase(particles.begin() + i);
		}
	}
}

void ParticleEmitter::Render(Camera* camera)
{
	for (Particle* p : particles) {
		p->Render(camera);
	}
}

void ParticleEmitter::RandomizeValues(Particle* p)
{
	p->SetSize(RandomRange(0.1f, 5.0f));
	glm::vec3 vel = glm::vec3(RandomRange(-1.0f, 1.0f), RandomRange(-1.0f, 1.0f), RandomRange(-1.0f, 1.0f));
	p->SetVelocity(vel);
	glm::vec3 col = glm::vec3(RandomRange(0, 1.0f), RandomRange(0, 1.0f), RandomRange(0, 1.0f));
	p->SetColour(col);
}

float ParticleEmitter::RandomRange(float min, float max)
{
	return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}
