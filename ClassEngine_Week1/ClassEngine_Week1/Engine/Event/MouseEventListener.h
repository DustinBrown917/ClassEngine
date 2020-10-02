#ifndef MOUSEEVENTLISTENER_H
#define MOUSEEVENTLISTENER_H

#include <SDL.h>
#include <glm/glm.hpp>

class CoreEngine;

class MouseEventListener
{
public:
	MouseEventListener(const MouseEventListener&) = delete; //Disable copy constructor lvalue
	MouseEventListener(MouseEventListener&&) = delete; //Disable move constructor lvalue
	MouseEventListener& operator = (const MouseEventListener&) = delete; //Disable copy constructor rvalue
	MouseEventListener& operator = (MouseEventListener&&) = delete; //Disable move constructor rvalue

	MouseEventListener() = delete;
	~MouseEventListener();

	static void RegisterEngineObject(CoreEngine* engine_);
	static void Update(SDL_Event e_);
	
	static void NotifyOfMousePressed(int buttonType_);
	static void NotifyOfMouseReleased(int buttonType_);
	static void NotifyOfMouseMove();
	static void NotifyOfMouseScroll(int y_);

	static glm::vec2 GetPrevMousePos();
	static glm::vec2 GetCurrentMousePos();
	static glm::vec2 GetMouseOffset();

private:
	static CoreEngine* engineInstance;
	static glm::vec2 mousePos, prevMousePos;
	static bool firstUpdate;
	static void UpdateMousePos();
};
#endif // !MOUSEEVENTLISTENER_H


