
#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "../../Engine/Core/CoreEngine.h"
#include "../../Engine/Rendering/Particles/ParticleEmitter.h"
#include <glm/gtx/string_cast.hpp>

class GameScene : public Scene
{
public:
	GameScene();
	virtual ~GameScene();

	// Inherited via Scene
	virtual bool OnCreate() override;
	virtual void Update(const float deltaTime_) override;
	virtual void Render() override;

	ParticleEmitter* emitter;

};
#endif // !GAMESCENE_H


