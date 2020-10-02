#ifndef MODEL_H
#define MODEL_H

#include "LoadOBJModel.h"
#include "Mesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <string>


class Model
{
public:
	Model(const std::string& objFilePath_, const std::string& mtlFilePath_, GLuint shaderProgram_);
	~Model();
	void Render(Camera* camera_);
	void AddMesh(Mesh* mesh);

	BoundingBox GetBoundingBox();
	glm::mat4 GetTransform(int index_) const;
	int CreateInstance(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_);
	void UpdateInstance(int index_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_);
	GLuint GetShaderProgram() const;
	
private:
	std::vector<Mesh*> subMeshes;
	GLuint shaderProgram;
	std::vector<glm::mat4> modelInstances;
	LoadOBJModel* obj;

	BoundingBox box;

	glm::mat4 GetTransform(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) const;
	void LoadModel();

};


#endif // !MODEL_H


