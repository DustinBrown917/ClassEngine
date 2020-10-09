#ifndef COMPONENT_H
#define COMPONENT_H

#include "../../Core/IGUISerializable.h"

class GameObject;

class Component : public IGUISerializable
{
public:
	Component() : gameObject(nullptr), guiEnabled(false) {}
	virtual ~Component() { gameObject = nullptr; }
	virtual bool OnCreate(GameObject* gameObject) = 0;
	virtual void Update(const float deltaTime_) = 0;

protected:
	GameObject* gameObject;
	bool guiEnabled;
};

#endif // ! COMPONENT_H



