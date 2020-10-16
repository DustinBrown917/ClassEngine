#include "CoreEngine.h"
#include "../imgui-master/imgui.h"
#include "../imgui-master/example/imgui_impl_sdl.h"
#include "../imgui-master/example/imgui_impl_opengl3.h"

std::unique_ptr<CoreEngine> CoreEngine::engineInstance = nullptr;

CoreEngine::CoreEngine() : isRunning(false), window(nullptr), gameInterface(nullptr), fps(120), currentSceneNum(0), camera(nullptr)
{
}


CoreEngine::~CoreEngine()
{
	OnDestroy();
}

bool CoreEngine::OnCreate(std::string name_, int width_, int height_)
{
	Debug::DebugInit();
	Debug::SetSeverity(MessageType::TYPE_INFO);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	window = new Window();

	if (!window->OnCreate(name_, width_, height_)) {
		Debug::FatalError("Window failed to initialize.", "CoreEngine.cpp", __LINE__);
		return isRunning = false;
	}

	SDL_WarpMouseInWindow(window->GetWindow(), window->GetWidth() * 0.5f, window->GetHeight() * 0.5f);
	MouseEventListener::RegisterEngineObject(this);

	ShaderHandler::GetInstance()->CreateProgram("ColourShader", "Engine/Shaders/ColourVertexShader.glsl", "Engine/Shaders/ColourFragmentShader.glsl");
	ShaderHandler::GetInstance()->CreateProgram("BasicShader", "Engine/Shaders/vertexShader.glsl", "Engine/Shaders/fragmentShader.glsl");

	if (gameInterface) {
		if (!gameInterface->OnCreate()) {
			Debug::Error("Could not create game interface.", "CoreEngine.cpp", __LINE__);
		}
	}

	timer.Start();

	Debug::Info("Everything worked!", "CoreEngine.cpp", __LINE__);

	return isRunning = true;
}

void CoreEngine::Run()
{
	while (isRunning) {
		timer.UpdateFrameTicks();
		EventListener::Update();
		Update(timer.GetDeltaTime());
		Render();
		SDL_Delay(timer.GetSleepTime(fps));
	}

	if (!isRunning) {
		OnDestroy();
	}
}

bool CoreEngine::GetIsRunning() const
{
	return isRunning;
}

CoreEngine * CoreEngine::GetInstance()
{
	if (engineInstance.get() == nullptr) {
		engineInstance.reset(new CoreEngine());
	}
	return engineInstance.get();
}

void CoreEngine::SetGameInterface(GameInterface * gameInterface_)
{
	gameInterface = gameInterface_;
}

int CoreEngine::GetCurrentScene()
{
	return currentSceneNum;
}

void CoreEngine::SetCurrentScene(int sceneNum_)
{
	currentSceneNum = sceneNum_;
}

void CoreEngine::Exit()
{
	isRunning = false;
}

glm::vec2 CoreEngine::GetWindowSize() const
{
	return glm::vec2(window->GetWidth(), window->GetHeight());
}

void CoreEngine::SetCamera(Camera* camera_)
{
	camera = camera_;
}

Camera* CoreEngine::GetCamera() const
{
	return camera;
}

void CoreEngine::NotifyOfMousePressed(glm::vec2 pos_, int buttonType_)
{
}

void CoreEngine::NotifyOfMouseReleased(glm::vec2 pos_, int buttonType_)
{
	CollisionHandler::GetInstance()->MouseUpdate(pos_, buttonType_);
}

void CoreEngine::NotifyOfMouseMove(glm::vec2 movement_)
{
	if (camera) {
		camera->ProcessMouseMovement(MouseEventListener::GetMouseOffset());
	}
	
}

void CoreEngine::NotifyOfMouseScroll(int y_)
{
	if (camera) {
		camera->ProcessMouseZoom(y_);
	}
	
}

void CoreEngine::Update(float deltaTime_)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(window->GetWindow());
	ImGui::NewFrame();

	if (gameInterface) {
		gameInterface->Update(deltaTime_);
	}
}

void CoreEngine::Render()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Draw all the things.

	if (gameInterface) {
		gameInterface->Render();
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	SDL_GL_SwapWindow(window->GetWindow());
}

void CoreEngine::OnDestroy()
{
	ShaderHandler::GetInstance()->OnDestroy();
	TextureHandler::GetInstance()->OnDestroy();
	MaterialHandler::GetInstance()->OnDestroy();
	CollisionHandler::GetInstance()->OnDestroy();
	SceneGraph::GetInstance()->OnDestroy();

	delete camera;
	camera = nullptr;

	delete gameInterface;
	gameInterface = nullptr;

	delete window;
	window = nullptr;
	
	SDL_Quit();
	exit(0);
}
