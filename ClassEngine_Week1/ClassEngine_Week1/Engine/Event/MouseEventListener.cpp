#include "MouseEventListener.h"
#include "../Core/CoreEngine.h"

CoreEngine* MouseEventListener::engineInstance = nullptr;
glm::vec2 MouseEventListener::mousePos = glm::vec2();
glm::vec2 MouseEventListener::prevMousePos = glm::vec2();
bool MouseEventListener::firstUpdate = true;

MouseEventListener::~MouseEventListener()
{
	engineInstance = nullptr;
}

void MouseEventListener::RegisterEngineObject(CoreEngine* engine_)
{
	engineInstance = engine_;
}

void MouseEventListener::Update(SDL_Event e_)
{
	if (e_.type == SDL_MOUSEBUTTONDOWN) {
		UpdateMousePos();
		NotifyOfMousePressed(e_.button.button);
	}
	else if (e_.type == SDL_MOUSEBUTTONUP) {
		UpdateMousePos();
		NotifyOfMouseReleased(e_.button.button);
	}
	else if (e_.type == SDL_MOUSEMOTION) {
		UpdateMousePos();
		NotifyOfMouseMove();
	}
	else if (e_.type == SDL_MOUSEWHEEL) {
		NotifyOfMouseScroll(e_.wheel.y);
	}
}

void MouseEventListener::NotifyOfMousePressed(int buttonType_)
{
	if (engineInstance) {
		engineInstance->NotifyOfMousePressed(mousePos, buttonType_);
	}
}

void MouseEventListener::NotifyOfMouseReleased(int buttonType_)
{
	if (engineInstance) {
		engineInstance->NotifyOfMouseReleased(mousePos, buttonType_);
	}
}

void MouseEventListener::NotifyOfMouseMove()
{
	if (engineInstance) {
		engineInstance->NotifyOfMouseMove(mousePos);
	}
}

void MouseEventListener::NotifyOfMouseScroll(int y_)
{
	if (engineInstance) {
		engineInstance->NotifyOfMouseScroll(y_);
	}
}

glm::vec2 MouseEventListener::GetPrevMousePos()
{
	return prevMousePos;
}

glm::vec2 MouseEventListener::GetCurrentMousePos()
{
	return mousePos;
}

glm::vec2 MouseEventListener::GetMouseOffset()
{
	return glm::vec2(mousePos.x - prevMousePos.x, prevMousePos.y - mousePos.y);
}

void MouseEventListener::UpdateMousePos()
{
	int tmpX, tmpY;
	SDL_GetMouseState(&tmpX, &tmpY);
	tmpY = engineInstance->GetWindowSize().y - tmpY;
	
	if (firstUpdate) {
		prevMousePos.x = mousePos.x = tmpX;
		prevMousePos.y = mousePos.y = tmpY;
		firstUpdate = false;
	}
	else {
		prevMousePos.x = mousePos.x;
		prevMousePos.y = mousePos.y;
		mousePos.x = tmpX;
		mousePos.y = tmpY;
	}

	
}
