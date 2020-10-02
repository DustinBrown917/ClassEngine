#include "GameObject.h"
#include "TestComponent.h"


bool TestComponent::OnCreate(GameObject* gameObject)
{
    this->gameObject = gameObject;
    return true;
}

void TestComponent::Update(const float deltaTime_)
{
    gameObject->SetAngle(gameObject->GetAngle() + rotationSpeed);
}

void TestComponent::SetRotationSpeed(float speed)
{
    rotationSpeed = speed;
}
