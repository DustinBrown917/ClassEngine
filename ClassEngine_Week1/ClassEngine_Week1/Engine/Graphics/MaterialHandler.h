
#ifndef MATERIALHANDLER_H
#define MATERIALHANDLER_H

#include <glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <memory>

struct Material {
	inline Material() : diffuseMap(0), shininess(0.0f), transparency(0.0f), ambient(glm::vec3(1.0f)), diffuse(glm::vec3(1.0f)), specular(glm::vec3()), name("") {

	}

	std::string name;

	GLuint diffuseMap; //newmtl

	float shininess; //ns*
	float transparency; //d*

	glm::vec3 ambient; //ka*
	glm::vec3 diffuse; //kd*
	glm::vec3 specular; //ks*
};

class MaterialHandler
{
public:

	MaterialHandler(const MaterialHandler&) = delete; //Disable copy constructor lvalue
	MaterialHandler(MaterialHandler&&) = delete; //Disable move constructor lvalue
	MaterialHandler& operator = (const MaterialHandler&) = delete; //Disable copy constructor rvalue
	MaterialHandler& operator = (MaterialHandler&&) = delete; //Disable move constructor rvalue

	static MaterialHandler* GetInstance();
	void AddMaterial(Material mat_);
	const Material GetMaterial(const std::string& matName_);
	void OnDestroy();

private:
	MaterialHandler();
	~MaterialHandler();

	static std::unique_ptr<MaterialHandler> instance;
	friend std::default_delete<MaterialHandler>;

	static std::vector<Material> materials;
};

#endif // !MATERIALHANDLER_H

