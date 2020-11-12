#include "Engine/Core/CoreEngine.h"
#include "Game/Game1.h"
#include "Engine/Core/SettingsManager.h"

int main(int argc, char* argv[]) {

	CoreEngine::GetInstance()->SetGameInterface(new Game1());
	SettingsManager::Init();
	SettingsManager::LoadSettings();

	WindowSettings ws = SettingsManager::GetWindowSettings();

	if (!CoreEngine::GetInstance()->OnCreate(ws.name, ws.width, ws.height)) {

		Debug::FatalError("Failed to create engine.", "Main.cpp", __LINE__);

		return 0;
	}

	CoreEngine::GetInstance()->Run();

	return 0;
}
