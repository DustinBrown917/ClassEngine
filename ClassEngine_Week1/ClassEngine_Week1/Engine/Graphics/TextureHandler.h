#ifndef TEXTUREHANDLER_H
#define TEXTUREHANDLER_H

#include <memory>
#include<string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "../Core/Debug.h"
#include <glew.h>

struct Texture {
	GLuint textureID = 0;
	float width = 0.0f;
	float height = 0.0f;
	std::string textureName = "";

};

class TextureHandler
{
public:

	TextureHandler(const TextureHandler&) = delete; //Disable copy constructor lvalue
	TextureHandler(TextureHandler&&) = delete; //Disable move constructor lvalue
	TextureHandler& operator = (const TextureHandler&) = delete; //Disable copy constructor rvalue
	TextureHandler& operator = (TextureHandler&&) = delete; //Disable move constructor rvalue

	static TextureHandler* GetInstance();
	void OnDestroy();

	void CreateTexture(const std::string& textureName_, const std::string& textureFilePath_);
	const GLuint GetTexture(const std::string& textureName_);
	const Texture* GetTextureData(const std::string& textureName_);


private:	


	TextureHandler();
	~TextureHandler();

	static std::unique_ptr<TextureHandler> textureInstance;
	friend std::default_delete<TextureHandler>;
	static std::vector<Texture*> textures;
};
#endif // !TEXTUREHANDLER_H


