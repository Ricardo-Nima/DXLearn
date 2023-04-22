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
	MSG msg;
	BOOL gResult;
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		DoFrame(1.0f);
	}
	if (gResult == -1)
	{
		throw CHWND_LAST_EXCEPT;
	}
	return msg.wParam;
}
void App::DoFrame(float dt)
{
	//execute at each frame
	//MousePosTest();
	TimerTest();
}

