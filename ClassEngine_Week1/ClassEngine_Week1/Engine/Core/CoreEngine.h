#ifndef COREENGINE_H
#define COREENGINE_H

#include <memory>
#include "Window.h"
#include "Timer.h"
#include "Debug.h"
#include "GameInterface.h"
#include "Scene.h"
#include "../Rendering/3D/GameObject.h"
#include "../Graphics/ShaderHandler.h"
#include "../Camera/Camera.h"
#include "../Graphics/TextureHandler.h"
#include "../Event/EventListener.h"
#include"../Rendering/SceneGraph.h"
#include "../Graphics/MaterialHandler.h"

class CoreEngine
{
public:


	CoreEngine(const CoreEngine&) = delete; //Disable copy constructor lvalue
	CoreEngine(CoreEngine&&) = delete; //Disable move constructor lvalue
	CoreEngine& operator = (const CoreEngine&) = delete; //Disable copy constructor rvalue
	CoreEngine& operator = (CoreEngine&&) = delete; //Disable move constructor rvalue



	bool OnCreate(std::string name_, int width_, int height_);
	void Run();
	bool GetIsRunning() const;

	static CoreEngine* GetInstance();

	void SetGameInterface(GameInterface* gameInterface_);
	int GetCurrentScene();
	void SetCurrentScene(int sceneNum_);
	void Exit();
	glm::vec2 GetWindowSize() const;

	void SetCamera(Camera* camera_);
	Camera* GetCamera() const;

	void NotifyOfMousePressed(glm::vec2 pos_, int buttonType_);
	void NotifyOfMouseReleased(glm::vec2 pos_, int buttonType_);
	void NotifyOfMouseMove(glm::vec2 movement_);
	void NotifyOfMouseScroll(int y_);

private:

	//Constructor/Destructor is made private for singletons
	CoreEngine();
	~CoreEngine();

	static std::unique_ptr<CoreEngine> engineInstance;
	friend std::default_delete<CoreEngine>;

	Window* window;
	bool isRunning;
	Timer timer;
	unsigned int fps;
	GameInterface* gameInterface;
	int currentSceneNum;
	Camera* camera;

	void Update(const float deltaTime_);
	void Render();
	void OnDestroy();
};

#endif // !COREENGINE_H


