#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

class Component
{
public:
	Component() : gameObject(nullptr) {}
	virtual ~Component() { gameObject = nullptr; }
	virtual bool OnCreate(GameObject* gameObject) = 0;
	virtual void Update(const float deltaTime_) = 0;

protected:
	GameObject* gameObject;
};

#endif // ! COMPONENT_H



