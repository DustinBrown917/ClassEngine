
#ifndef SHADERHANDLER_H
#define SHADERHANDLER_H

#include <sstream>
#include <map>
#include <vector>
#include <memory>
#include <glew.h>
#include "../Core/Debug.h"

class ShaderHandler
{
public:

	ShaderHandler(const ShaderHandler&) = delete; //Disable copy constructor lvalue
	ShaderHandler(ShaderHandler&&) = delete; //Disable move constructor lvalue
	ShaderHandler& operator = (const ShaderHandler&) = delete; //Disable copy constructor rvalue
	ShaderHandler& operator = (ShaderHandler&&) = delete; //Disable move constructor rvalue

	static ShaderHandler* GetInstance();

	void CreateProgram(const std::string& shaderName_, const std::string& vertexShaderFileName_, const std::string& fragmentShaderFileName_);
	GLuint GetShader(const std::string& shaderName_);
	void OnDestroy();
private:
	static std::unique_ptr<ShaderHandler> shaderInstance;
	friend std::default_delete<ShaderHandler>;

	ShaderHandler();
	~ShaderHandler();

	std::string ReadShader(const std::string& filePath_);
	GLuint CreateShader(GLenum shaderType_, const std::string& source_, const std::string& shaderName_);

	static std::map<std::string, GLuint> programs;
};
#endif // !SHADERHANDLER_H


