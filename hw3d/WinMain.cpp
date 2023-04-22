#include "Window.h"
#include "StringConverter.h"
#include <sstream>

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int   nCmdShow)
{
	try
	{
		Window wnd(640, 480, L"My Window");
		//Window wnd2(300, 600, L"My Window2");

		//dump message
		MSG msg;
		BOOL ret;
		while ((ret = GetMessage(&msg, nullptr, 0, 0)) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
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
	}
	catch (const ChiliException& e)
	{
		MessageBox(nullptr, e.wWhat(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{
		MessageBox(nullptr, StringConverter::s2ws(e.what()).c_str(), L"Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, L"No details available", L"Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	return -1;
}