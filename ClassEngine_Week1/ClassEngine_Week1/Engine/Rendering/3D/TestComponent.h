#ifndef TESTCOMPONENT_H
#define TESTCOMPONENT_H

#include "Component.h"

class TestComponent : public Component {
public:
	TestComponent() : Component() {}
	virtual ~TestComponent() { }
	virtual bool OnCreate(GameObject* gameObject) override;
	virtual void Update(const float deltaTime_) override;
	void SetRotationSpeed(float speed);

private:
	float rotationSpeed = 0.005f;
};

#endif // !TESTCOMPONENT_H

