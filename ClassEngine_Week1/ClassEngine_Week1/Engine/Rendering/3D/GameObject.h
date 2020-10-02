#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"
#include "Component.h"
#include <type_traits>
#include <typeinfo>

class GameObject
{
public:
	GameObject(Model* model_, glm::vec3 position_ = glm::vec3());
	~GameObject();
	void Render(Camera* camera_);
	void Update( const float deltaTime);

	glm::vec3 GetPosition() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;
	float GetAngle() const;
	BoundingBox GetBoundingBox();
	std::string GetTag() const;
	bool GetHit() const;


	void SetPositon(glm::vec3 position_);
	void SetRotation(glm::vec3 rotation_);
	void SetScale(glm::vec3 scale_);
	void SetAngle(float angle_);
	void SetTag(std::string tag_);
	void SetHit(const bool hit_, int buttonType_);

	template<typename T>
	void AddComponent() {
		if (std::is_base_of<Component, T>::value) {

			for (Component* c : components)
			{
				if (typeid(*c) == typeid(T)) {
					std::cout << "Component of type \"" << typeid(T).name() << "\" already exists on GameObject.\n";
					return;
				}
			}

			components.push_back(new T());
			components.back()->OnCreate(this);
			std::cout << "Component \"" << typeid(T).name() << "\" added. Current component count: " << components.size() << "\n";
		}
		else {
			std::cout << typeid(T).name() << " does not inherit from Component!\n";
		}
	}

	template<typename T>
	T* GetComponent()
	{
		T* comp = nullptr;
		if (std::is_base_of<Component, T>::value) {

			for (Component* c : components)
			{
				if (typeid(*c) == typeid(T)) {
					//If we're here, we're sure that c is of type T. Static cast should suffice.
					comp = static_cast<T*>(c);
				}
			}
		}
		else {
			std::cout << typeid(T).name() << " does not inherit from Component!\n";
		}

		return comp;
	}

	template<typename T>
	void RemoveComponent()
	{
		if (std::is_base_of<Component, T>::value) {
			for (int i = 0; i < components.size(); i++) {
				if (typeid(*components[i]) == typeid(T)) {
					components.erase(components.begin() + i);
					std::cout << "Removed! Remaining components: " << components.size() << "\n";
					return;
				}
			}
		}
		else {
			std::cout << typeid(T).name() << " does not inherit from Component!\n";
		}
	}

private:
	Model* model;
	glm::vec3 position, rotation, scale;
	float angle;

	int modelInstance;

	BoundingBox box;

	std::string tag;

	bool hit;

	std::vector<Component*> components;
};


#endif // !GAMEOBJECT_H

