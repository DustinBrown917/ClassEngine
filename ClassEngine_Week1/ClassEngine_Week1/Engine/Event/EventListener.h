#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include "MouseEventListener.h"

class EventListener {

public:
	EventListener(const EventListener&) = delete; //Disable copy constructor lvalue
	EventListener(EventListener&&) = delete; //Disable move constructor lvalue
	EventListener& operator = (const EventListener&) = delete; //Disable copy constructor rvalue
	EventListener& operator = (EventListener&&) = delete; //Disable move constructor rvalue

	EventListener() = delete;
	~EventListener();

	static void Update();

};

#endif // !EVENTLISTENER_H

