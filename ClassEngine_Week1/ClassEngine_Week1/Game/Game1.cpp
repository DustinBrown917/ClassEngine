#include "Game1.h"
#include "Scenes/StartScene.h"
#include "Scenes/GameScene.h"

Game1::Game1() : GameInterface(), currentSceneNum(0), currentScene(nullptr)
{
}

Game1::~Game1()
{
	delete currentScene;
	currentScene = nullptr;
}

bool Game1::OnCreate()
{
	if (CoreEngine::GetInstance()->GetCurrentScene() == 0) {
		currentScene = new StartScene();
		currentSceneNum = 0;
		return currentScene->OnCreate();
	}
	Debug::FatalError("Engine's Scene is not initialized to 0.", "Game1.cpp", __LINE__);
	return false;
}

void Game1::Update(const float deltaTime_)
{
	if (currentSceneNum != CoreEngine::GetInstance()->GetCurrentScene()) {
		BuildScene();
	}
	currentScene->Update(deltaTime_);
}

void Game1::Render()
{
	currentScene->Render();
}

void Game1::BuildScene()
{
	delete currentScene;
	currentScene = nullptr;

	int engineSceneNum = CoreEngine::GetInstance()->GetCurrentScene();

	switch (engineSceneNum)
	{
		case 1:
			currentScene = new GameScene();
			break;
		default:
			currentScene = new StartScene();
			break;
	}

	currentSceneNum = engineSceneNum;

	if (!currentScene->OnCreate()) {
		Debug::FatalError("Scene failed to build.", "Game1.cpp", __LINE__);
		CoreEngine::GetInstance()->Exit();
	}
}
