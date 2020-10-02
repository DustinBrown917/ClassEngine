#ifndef GAME1_H
#define GAME1_H

#include "../Engine/Core/CoreEngine.h"

class Game1 : public GameInterface
{
public:
	Game1();
	virtual ~Game1();

	// Inherited via GameInterface
	virtual bool OnCreate() override;
	virtual void Update(const float deltaTime_) override;
	virtual void Render() override;

private:
	int currentSceneNum;
	Scene* currentScene;
	void BuildScene();
};
#endif // !GAME1_H


