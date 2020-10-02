#ifndef MATERIALLOADER_H
#define MATERIALLOADER_H

#include "../Graphics/MaterialHandler.h"
#include "../Graphics/TextureHandler.h"
#include <sstream>

class MaterialLoader
{
public:
	MaterialLoader(const MaterialLoader&) = delete; //Disable copy constructor lvalue
	MaterialLoader(MaterialLoader&&) = delete; //Disable move constructor lvalue
	MaterialLoader& operator = (const MaterialLoader&) = delete; //Disable copy constructor rvalue
	MaterialLoader& operator = (MaterialLoader&&) = delete; //Disable move constructor rvalue

	MaterialLoader() = delete;
	~MaterialLoader();

	static void LoadMaterial(std::string filePath_);
private:
	static GLuint LoadTexture(std::string fileName_);
};

#endif // !MATERIALLOADER_H


