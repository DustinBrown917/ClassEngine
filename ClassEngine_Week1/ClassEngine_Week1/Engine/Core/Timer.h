#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

class Timer
{
public:
	Timer(const Timer&) = delete; //Disable copy constructor lvalue
	Timer(Timer&&) = delete; //Disable move constructor lvalue
	Timer& operator = (const Timer&) = delete; //Disable copy constructor rvalue
	Timer& operator = (Timer&&) = delete; //Disable move constructor rvalue

	Timer();
	~Timer();
	void Start();
	void UpdateFrameTicks();
	float GetDeltaTime() const;
	unsigned int GetSleepTime(const unsigned int fps_);
	float GetCurrentTick() const; 

private:
	unsigned int prevTicks, currentTicks;
};
#endif // !TIMER_H


