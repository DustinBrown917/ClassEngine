#include "Engine/Core/CoreEngine.h"
#include "Game/Game1.h"

int main(int argc, char* argv[]) {

	CoreEngine::GetInstance()->SetGameInterface(new Game1());

	if (!CoreEngine::GetInstance()->OnCreate("Engine Window", 1280, 720)) {

		Debug::FatalError("Failed to create engine.", "Main.cpp", __LINE__);

		return 0;
	}

	CoreEngine::GetInstance()->Run();

	return 0;
}
