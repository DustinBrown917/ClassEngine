#ifndef TESTCOMPONENT_H
#define TESTCOMPONENT_H

#include "Component.h"

class TestComponent : public Component {
public:
	TestComponent() : Component() {}
	virtual ~TestComponent() { }
	virtual bool OnCreate(GameObject* gameObject) override;
	virtual void Update(const float deltaTime_) override;
	virtual void SetGuiEnabled(const bool enabled) override;
	virtual bool GuiEnabled() override;
	virtual void UpdateGUI(const float deltaTime) override;
	void SetRotationSpeed(float speed);

private:
	float rotationSpeed = 0.0f;
};

#endif // !TESTCOMPONENT_H

