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
		MousePosTest();
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
}
void App::MousePosTest()
{
	while (!wnd.mouse.IsEmpty())
	{
		const auto e = wnd.mouse.Read();
		if (!e.has_value()) {
			break;
		}
		const auto& eVal = e.value();
		if (eVal.GetType() == Mouse::Event::Type::Move) {
			std::wstringstream oss;
			oss << L"Mouse Position: (" << eVal.GetPosX() << L", " << eVal.GetPosY() << L") ";
			wnd.SetTitle(oss.str());
		}
	}
}
