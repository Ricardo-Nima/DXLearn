#include "App.h"
#include <sstream>

App::App()
	:
	wnd(800, 600, L"My Window")
{}
App::~App()
{}

int App::Go()
{
	while (true)
	{
		const auto eCode = Window::ProcessMessage();
		if (eCode.has_value())
			return *eCode;
		DoFrame(1.0f);
	}
}
void App::DoFrame(float dt)
{
	//execute at each frame
	//MousePosTest();
	TimerTest();
	const float c = sin(timer.Peek()) / 2.0f + 0.5f;
	wnd.GetGfx().ClearBuffer(c, c, 1.0f);
	wnd.GetGfx().EndFrame();
}

