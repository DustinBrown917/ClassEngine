#include "GameObject.h"
#include "TestComponent.h"
#include "../../../Engine/imgui-master/imgui.h"

GameObject::GameObject(Model * model_, glm::vec3 position_) : model(nullptr), components(std::vector<Component*>()), guiEnabled(false)
{
	model = model_;
	position = position_;
	angle = 0.0f;
	rotation = glm::vec3(0.0f, 1.0f, 0.0f);
	scale = glm::vec3(1.0f);
	tag = "";
	hit = false;
	if (model_) {
		modelInstance = model->CreateInstance(position, angle, rotation, scale);
		box = model->GetBoundingBox();
		box.transform = model->GetTransform(modelInstance);
	}	
}

GameObject::~GameObject()
{
	if (components.size() > 0) {
		for (auto c : components) {
			delete c;
			c = nullptr;
		}
		components.clear();
	}

	model = nullptr;
}

void GameObject::Render(Camera* camera_)
{
	if (model) {
		model->Render(camera_);
	}
}

void GameObject::Update(const float deltaTime)
{
	for (Component* c : components) {
		c->Update(deltaTime);
	}
	UpdateGUI(deltaTime);
}

glm::vec3 GameObject::GetPosition() const
{
	return position;
}

glm::vec3 GameObject::GetRotation() const
{
	return rotation;
}

glm::vec3 GameObject::GetScale() const
{
	return scale;
}

float GameObject::GetAngle() const
{
	return angle;
}

BoundingBox GameObject::GetBoundingBox()
{
	return box;
}

std::string GameObject::GetTag() const
{
	return tag;
}

bool GameObject::GetHit() const
{
	return hit;
}

void GameObject::SetPositon(glm::vec3 position_)
{
	position = position_;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		box.transform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetRotation(glm::vec3 rotation_)
{
	rotation = rotation_;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		box.transform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetScale(glm::vec3 scale_)
{
	scale = scale_;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		box.transform = model->GetTransform(modelInstance);
		box.minVert *= (scale.x > 1.0f) ? 1.0f : (scale.x * 0.5f);
		box.maxVert *= (scale.x > 1.0f) ? 1.0f : (scale.x * 0.5f);
	}
}

void GameObject::SetAngle(float angle_)
{
	angle = angle_;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		box.transform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetTag(std::string tag_)
{
	tag = tag_;
}

void GameObject::SetHit(const bool hit_, int buttonType_)
{
	hit = hit_;

	if (hit) {
		SetGuiEnabled(!guiEnabled);
	}
}

void GameObject::SetGuiEnabled(const bool enabled)
{
	guiEnabled = enabled;
}

bool GameObject::GuiEnabled()
{
	return guiEnabled;
}

void GameObject::UpdateGUI(const float deltaTime)
{
	if (!guiEnabled) { return; }

	ImGui::Begin(tag.c_str());

	ImGui::InputFloat3("Position", glm::value_ptr(position), 3);

	if (ImGui::Button("Add Spinner")) {
		AddComponent<TestComponent>();
	}

	for (Component* c : components) {
		c->UpdateGUI(deltaTime);
	}

	ImGui::End();
}

