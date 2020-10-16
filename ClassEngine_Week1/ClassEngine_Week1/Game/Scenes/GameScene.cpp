#include"../../Engine/Rendering/3D/TestComponent.h"
#include "../../Engine/Core/Audio/AudioHandler.h"
#include "GameScene.h"


GameScene::GameScene() : Scene()
{

}

GameScene::~GameScene()
{
	SceneGraph::GetInstance()->OnDestroy();
	AudioHandler::GetInstance()->OnDestroy();
}

bool GameScene::OnCreate()
{
	Debug::Info("Creating game scene.", "GameScene.cpp", __LINE__);

	CoreEngine::GetInstance()->SetCamera(new Camera());
	CoreEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), 0.1f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f)));
	
	if (!AudioHandler::GetInstance()->OnCreate(CoreEngine::GetInstance()->GetCamera()->GetPosition())) {
		Debug::Error("Failed to create audio manager.", "GameScene.cpp", __LINE__);
		return false;
	}
	
	CollisionHandler::GetInstance()->OnCreate(100.0f);

	//Makin a model.
	{

		Model* model1 = new Model("./Resources/Models/Dice.obj", "./Resources/Materials/Dice.mtl", ShaderHandler::GetInstance()->GetShader("BasicShader"));
		SceneGraph::GetInstance()->AddModel(model1);
		Model* model2 = new Model("./Resources/Models/Apple.obj", "./Resources/Materials/Apple.mtl", ShaderHandler::GetInstance()->GetShader("BasicShader"));

		SceneGraph::GetInstance()->AddModel(model2);

		GameObject* dice = new GameObject(model1);
		SceneGraph::GetInstance()->AddGameObject(dice, "bl_die");
		dice->AddComponent<TestComponent>();
		dice->SetPositon(glm::vec3(-4.25f, -4.25f, -10.0f));
		dice->GetComponent<TestComponent>()->SetRotationSpeed(0.001f);
		dice->AddComponent<AudioSource>("loop.wav", true, false, true);

		GameObject* dice2 = new GameObject(model1);
		SceneGraph::GetInstance()->AddGameObject(dice2, "tl_die");
		dice2->SetPositon(glm::vec3(-4.25f, 4.25f, -10.0f));
		dice2->AddComponent<TestComponent>();
		dice2->GetComponent<TestComponent>()->SetRotationSpeed(0.5f);

		GameObject* dice3 = new GameObject(model1);
		SceneGraph::GetInstance()->AddGameObject(dice3, "tr_die");
		dice3->SetPositon(glm::vec3(4.25, 4.25f, -10.0f));
		dice3->AddComponent<TestComponent>();


		GameObject* dice4 = new GameObject(model1);
		SceneGraph::GetInstance()->AddGameObject(dice4, "br_die");
		dice4->SetPositon(glm::vec3(4.25, -4.25f, -10.0f));
		dice4->AddComponent<TestComponent>();
		dice4->RemoveComponent<TestComponent>();

		GameObject* apple = new GameObject(model2);
		SceneGraph::GetInstance()->AddGameObject(apple, "apple");

		apple->SetScale(glm::vec3(0.5f));
		apple->SetPositon(glm::vec3(0, 0, -10));
		apple->AddComponent<TestComponent>();
		apple->GetComponent<TestComponent>()->SetRotationSpeed(-0.01f);

		apple->AddComponent<AudioSource>("click.wav", false, true, false);
	}

	return true;
}

void GameScene::Update(const float deltaTime_)
{
	SceneGraph::GetInstance()->Update(deltaTime_);
}

void GameScene::Render()
{
	SceneGraph::GetInstance()->Render(CoreEngine::GetInstance()->GetCamera());
}
