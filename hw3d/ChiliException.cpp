#include "ChiliException.h"
#include <sstream>


ChiliException::ChiliException(int line, const wchar_t* file) noexcept
	:
	line(line),
	file(file)
{}

const wchar_t* ChiliException::wWhat() const noexcept
{
	std::wstringstream oss;
	oss << GetType() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const wchar_t* ChiliException::GetType() const noexcept
{
	return L"Chili Exception";
}

int ChiliException::GetLine() const noexcept
{
	return line;
}

const std::wstring& ChiliException::GetFile() const noexcept
{
	return file;
}

std::wstring ChiliException::GetOriginString() const noexcept
{
	std::wstringstream oss;
	oss << "[File] " << file << std::endl
		<< "[Line] " << line;
	return oss.str();
}