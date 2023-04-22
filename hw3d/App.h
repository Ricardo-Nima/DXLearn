#pragma once
#include "Window.h"
#include "ChiliTimer.h"
class App
{
public:
	App();
	// master frame / message loop
	int Go();
	~App();
private:
	void DoFrame(float dt);
	void MousePosTest();
	void TimerTest();
private:
	Window wnd;
	ChiliTimer timer;
};

