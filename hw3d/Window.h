#pragma once
#include "ChiliWin.h"
#include "ChiliException.h"
#include <optional>
#include <memory>
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"


class Window
{
public:
	class Exception : public ChiliException
	{
		using ChiliException::ChiliException;
	public:
		static std::wstring TranslateErrorCode(HRESULT hr) noexcept;
	};
	class HrException : public Exception
	{
	public:
		HrException(int line, const char* file, HRESULT hr) noexcept;
		HrException(int line, const wchar_t* file, HRESULT hr) noexcept;
		const wchar_t* wWhat() const noexcept override;
		const wchar_t* GetType() const noexcept override;
		HRESULT GetErrorCode() const noexcept;
		std::wstring GetErrorDescription() const noexcept;
	private:
		HRESULT hr;
	};
	class NoGfxException : public Exception
	{
	public:
		NoGfxException(int line, const char* file) noexcept;
		NoGfxException(int line, const wchar_t* file) noexcept;
		const wchar_t* GetType() const noexcept override;
	};
private:
	// singleton manages registration/cleanup of window class
	class WindowClass
	{
	public:
		static const wchar_t* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		WindowClass();
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;
		static constexpr const wchar_t* wndClassName = L"Chili Direct3D Engine Window";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};
public:
	Window(int width, int height, const wchar_t* name);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	void SetTitle(const std::wstring& title);
	static std::optional<int> ProcessMessage() noexcept;
	Graphics& GetGfx();
private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
public:
	Keyboard kbd;
	Mouse mouse;
private:
	int width;
	int height;
	HWND hWnd;
	std::unique_ptr<Graphics> pGfx;
};

#define CHWND_EXCEPT(hr) Window::HrException(__LINE__, __FILE__, hr)
#define CHWND_LAST_EXCEPT Window::HrException(__LINE__, __FILE__, GetLastError())
#define CHWND_NOGFX_EXCEPT() Window::NoGfxException( __LINE__,__FILE__ )

