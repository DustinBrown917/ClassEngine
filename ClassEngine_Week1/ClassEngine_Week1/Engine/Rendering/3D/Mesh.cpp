#include <iostream>
#include "Mesh.h"

Mesh::Mesh(SubMesh subMesh_, GLuint shaderProgram_) : VAO(0), VBO(0), modelLocation(0), viewLoc(0), projLoc(0)
{
	shaderProgram = shaderProgram_;
	subMesh = subMesh_;
	GenerateBuffers();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	if (subMesh.vertexList.size() > 0) {
		subMesh.vertexList.clear();
	}

	if (subMesh.meshIndices.size() > 0) {
		subMesh.meshIndices.clear();
	}
}

void Mesh::Render(Camera* camera_, std::vector<glm::mat4> instances_)
{
	

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, subMesh.material.diffuseMap);

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));

	glUniform1f(matShine, subMesh.material.shininess);
	glUniform1f(matTrans, subMesh.material.transparency);
	glUniform3fv(matAmb, 1, glm::value_ptr(subMesh.material.ambient));
	glUniform3fv(matDiff, 1, glm::value_ptr(subMesh.material.diffuse));
	glUniform3fv(matSpec, 1, glm::value_ptr(subMesh.material.specular));

	LightSource* light = camera_->GetLightSources()[0];

	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));
	glUniform3fv(viewPos, 1, glm::value_ptr(camera_->GetPosition()));

	glUniform3fv(lightPos, 1, glm::value_ptr(light->GetPosition()));
	glUniform1f(lightAmbVal, light->GetAmbientValue());
	glUniform1f(lightDiffVal, light->GetDiffuseValue());
	glUniform3fv(lightColVal, 1, glm::value_ptr(light->GetColour()));


	glBindVertexArray(VAO);
	for (int i = 0; i < instances_.size(); i++) {
		glm::vec3 pos = glm::vec3(instances_[i][3].x, instances_[i][3].y, instances_[i][3].z);
		if (!camera_->IsInFrustum(pos)) {
			continue; 
		}
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(instances_[i]));
		glDrawArrays(GL_TRIANGLES, 0, subMesh.vertexList.size());
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex), &subMesh.vertexList[0], GL_STATIC_DRAW);

	//POSITION
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	//NORMAL
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	//TEXTCOORD
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textCoord));
	
	//COLOUR
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, colour));


	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	modelLocation = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projLoc = glGetUniformLocation(shaderProgram, "proj");
	

	viewPos = glGetUniformLocation(shaderProgram, "cameraPos");
	lightPos = glGetUniformLocation(shaderProgram, "light.position");
	lightAmbVal = glGetUniformLocation(shaderProgram, "light.ambient");
	lightDiffVal = glGetUniformLocation(shaderProgram, "light.diffuse");
	lightColVal = glGetUniformLocation(shaderProgram, "light.colour");

	matShine = glGetUniformLocation(shaderProgram, "material.shininess");
	matTrans = glGetUniformLocation(shaderProgram, "material.transparency");
	matAmb = glGetUniformLocation(shaderProgram, "material.ambient");
	matDiff = glGetUniformLocation(shaderProgram, "material.diffuse");
	matSpec = glGetUniformLocation(shaderProgram, "material.specular");
}
