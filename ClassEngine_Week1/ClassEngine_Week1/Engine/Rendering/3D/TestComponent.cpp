#include "GameObject.h"
#include "TestComponent.h"
#include "../../../Engine/imgui-master/imgui.h"


bool TestComponent::OnCreate(GameObject* gameObject)
{
    guiEnabled = true;
    this->gameObject = gameObject;
    return true;
}

void TestComponent::Update(const float deltaTime_)
{
    gameObject->SetAngle(gameObject->GetAngle() + rotationSpeed);
}

void TestComponent::SetGuiEnabled(const bool enabled)
{
    guiEnabled = enabled;
}

bool TestComponent::GuiEnabled()
{
    return guiEnabled;
}

void TestComponent::UpdateGUI(const float deltaTime)
{
    if (!guiEnabled) { return; }
    ImGui::SliderFloat("Speed", &rotationSpeed, -1.0f, 1.0f);
    if (ImGui::Button("Remove Spinner")) {
        gameObject->RemoveComponent<TestComponent>();
    }
    
}

void TestComponent::SetRotationSpeed(float speed)
{
    rotationSpeed = speed;
}
