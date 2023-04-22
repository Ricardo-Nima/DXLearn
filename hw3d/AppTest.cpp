#include "App.h"

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
void App::TimerTest()
{
	float duration = timer.Peek();
	std::wstringstream oss;
	oss << L"Time elapsed: " << duration;
	wnd.SetTitle(oss.str());
}