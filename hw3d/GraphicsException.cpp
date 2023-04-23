#include "Graphics.h"
#include <sstream>
#include <iomanip>
#include "StringConverter.h"
#include "dxerr.h"
// Graphics exception stuff
Graphics::HrException::HrException(int line, const char* file, HRESULT hr, std::vector<std::wstring> infoMsgs) noexcept
	:
	Exception(line, StringConverter::s2ws(string(file)).c_str()),
	hr(hr)
{
	// join all info messages with newlines into single string
	for (const auto& m : infoMsgs)
	{
		info += m;
		info.push_back('\n');
	}
	// remove final newline if exists
	if (!info.empty())
	{
		info.pop_back();
	}
}
Graphics::HrException::HrException(int line, const wchar_t* file, HRESULT hr, std::vector<std::wstring> infoMsgs) noexcept
	:
	Exception(line, file),
	hr(hr)
{
	// join all info messages with newlines into single string
	for (const auto& m : infoMsgs)
	{
		info += m;
		info.push_back(L'\n');
	}
	// remove final newline if exists
	if (!info.empty())
	{
		info.pop_back();
	}
}

const wchar_t* Graphics::HrException::wWhat() const noexcept
{
	std::wstringstream oss;
	oss << GetType() << std::endl
		<< L"[Error Code] 0x" << std::hex << std::uppercase << GetErrorCode()
		<< std::dec << " (" << (unsigned long)GetErrorCode() << ")" << std::endl
		<< "[Error String] " << GetErrorString() << std::endl
		<< "[Description] " << GetErrorDescription() << std::endl;
	if (!info.empty())
	{
		oss << "\n[Error Info]\n" << GetErrorInfo() << std::endl << std::endl;
	}
	oss << GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const wchar_t* Graphics::HrException::GetType() const noexcept
{
	return L"Chili Graphics Exception";
}

HRESULT Graphics::HrException::GetErrorCode() const noexcept
{
	return hr;
}

std::wstring Graphics::HrException::GetErrorString() const noexcept
{
	return DXGetErrorString(hr);
}

std::wstring Graphics::HrException::GetErrorDescription() const noexcept
{
	wchar_t buf[512];
	DXGetErrorDescription(hr, buf, sizeof(buf));
	return buf;
}

std::wstring Graphics::HrException::GetErrorInfo() const noexcept
{
	return info;
}


const wchar_t* Graphics::DeviceRemovedException::GetType() const noexcept
{
	return L"Chili Graphics Exception [Device Removed] (DXGI_ERROR_DEVICE_REMOVED)";
}

//Graphics::InfoException::InfoException(int line, const char* file, std::vector<std::string> infoMsgs) noexcept
//	:
//	Exception(line, file)
//{
//	// join all info messages with newlines into single string
//	for (const auto& m : infoMsgs)
//	{
//		info += m;
//		info.push_back('\n');
//	}
//	// remove final newline if exists
//	if (!info.empty())
//	{
//		info.pop_back();
//	}
//}
//
//
//const char* Graphics::InfoException::what() const noexcept
//{
//	std::ostringstream oss;
//	oss << GetType() << std::endl
//		<< "\n[Error Info]\n" << GetErrorInfo() << std::endl << std::endl;
//	oss << GetOriginString();
//	whatBuffer = oss.str();
//	return whatBuffer.c_str();
//}

//const char* Graphics::InfoException::GetType() const noexcept
//{
//	return "Chili Graphics Info Exception";
//}
//
//std::string Graphics::InfoException::GetErrorInfo() const noexcept
//{
//	return info;
//}
