#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Camera/Camera.h"
#include "../../Graphics/MaterialHandler.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textCoord;
	glm::vec3 colour;

};

struct SubMesh {
	std::vector<Vertex> vertexList;
	std::vector<int> meshIndices;
	Material material;
};

class Mesh
{
public:
	Mesh(SubMesh subMesh_, GLuint shaderProgram_);
	~Mesh();

	void Render(Camera* camera, std::vector<glm::mat4> instances_);

private:	
	GLuint VAO, VBO;
	GLuint shaderProgram;
	GLuint modelLocation, viewLoc, projLoc;
	GLuint viewPos, lightPos, lightAmbVal, lightDiffVal, lightColVal;
	GLuint matShine, matTrans, matAmb, matDiff, matSpec;
	SubMesh subMesh;

	void GenerateBuffers();
};


#endif // !MESH_H


