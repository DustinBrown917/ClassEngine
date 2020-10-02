#include "GameObject.h"
#include "TestComponent.h"

GameObject::GameObject(Model * model_, glm::vec3 position_) : model(nullptr), components(std::vector<Component*>())
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
	//SetAngle(angle + 0.005f);
	for (Component* c : components) {
		c->Update(deltaTime);
	}
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
		std::cout << tag << " has been hit!\n";
	}
}

//template<typename T> 
//void GameObject::AddComponent() {
//	if (std::is_base_of<Component, T>::value) {
//
//		for(Component* c : components)
//		{
//			if (typeid(*c) == typeid(T)) {
//				std::cout << "Component of type \"" << typeid(T).name() << "\" already exists on GameObject.\n";
//				return;
//			}
//		}
//
//		components.push_back(new T());
//		components.back()->OnCreate(this);
//		std::cout << "Component \"" << typeid(T).name()<<"\" added. Current component count: " << components.size() << "\n";
//	}
//	else {
//		std::cout << typeid(T).name()<< " does not inherit from Component!\n";
//	}
//}
//
//template<typename T>
//T* GameObject::GetComponent()
//{
//	T* comp = nullptr;
//	if (std::is_base_of<Component, T>::value) {
//
//		for (Component* c : components)
//		{
//			if (typeid(*c) == typeid(T)) {	
//				//If we're here, we're sure that c is of type T. Static cast should suffice.
//				comp = static_cast<T*>(c);
//			}
//		}
//	}
//	else {
//		std::cout << typeid(T).name() << " does not inherit from Component!\n";
//	}
//
//	return comp;
//}
//
//template<typename T>
//void GameObject::RemoveComponent()
//{
//	if (std::is_base_of<Component, T>::value) {
//		for (int i = 0; i < components.size(); i++) {
//			if (typeid(*components[i]) == typeid(T)) {
//				components.erase(components.begin() + i);
//				std::cout << "Removed! Remaining components: " << components.size() << "\n";
//				return;
//			}
//		}
//	}
//	else {
//		std::cout << typeid(T).name() << " does not inherit from Component!\n";
//	}
//}
