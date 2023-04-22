#pragma once
#include "Window.h"
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
private:
	Window wnd;
};

