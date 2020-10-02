#ifndef STARTSCENE_H
#define STARTSCENE_H

#include "../../Engine/Core/CoreEngine.h"

class StartScene : public Scene
{
public:

	StartScene();
	virtual ~StartScene();

	// Inherited via Scene
	virtual bool OnCreate() override;
	virtual void Update(const float deltaTime_) override;
	virtual void Render() override;
};

#endif // !STARTSCENE_H

