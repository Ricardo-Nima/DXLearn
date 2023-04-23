#include "Window.h"
#include <sstream>
#include "StringConverter.h"
// Window Exception Stuff
std::wstring Window::Exception::TranslateErrorCode(HRESULT hr) noexcept
{
	wchar_t* pMsgBuf = nullptr;
	// windows will allocate memory for err string and make our pointer point to it
	const DWORD nMsgLen = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPWSTR>(&pMsgBuf), 0, nullptr
	);
	// 0 string length returned indicates a failure
	if (nMsgLen == 0)
	{
		return L"Unidentified error code";
	}
	// copy error string from windows-allocated buffer to std::string
	std::wstring errorString = pMsgBuf;
	// free windows buffer
	LocalFree(pMsgBuf);
	return errorString;
}
Window::HrException::HrException(int line, const wchar_t* file, HRESULT hr) noexcept
	:
	Exception(line, file),
	hr(hr)
{}

Window::HrException::HrException(int line, const char* file, HRESULT hr) noexcept
	:
	Exception(line, StringConverter::s2ws(string(file)).c_str()),
	hr(hr)
{}

const wchar_t* Window::HrException::wWhat() const noexcept
{
	std::wstringstream oss;
	oss << GetType() << std::endl
		<< "[Error Code] 0x" << std::hex << std::uppercase << GetErrorCode()
		<< std::dec << " (" << (unsigned long)GetErrorCode() << ")" << std::endl
		<< "[Description] " << GetErrorDescription() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const wchar_t* Window::HrException::GetType() const noexcept
{
	return L"Chili Window Exception";
}

HRESULT Window::HrException::GetErrorCode() const noexcept
{
	return hr;
}

std::wstring Window::HrException::GetErrorDescription() const noexcept
{
	return Exception::TranslateErrorCode(hr);
}


//NoGfxException
Window::NoGfxException::NoGfxException(int line, const wchar_t* file) noexcept
	:
	Exception(line, file)
{}

Window::NoGfxException::NoGfxException(int line, const char* file) noexcept
	:
	Exception(line, StringConverter::s2ws(string(file)).c_str())
{}
const wchar_t* Window::NoGfxException::GetType() const noexcept
{
	return L"Chili NoGfxException";
}