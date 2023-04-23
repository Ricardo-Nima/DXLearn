#pragma once
#include <d3d11.h>
#include <vector>
#include "ChiliWin.h"
#include "ChiliException.h"
class Graphics
{
public:
	class Exception : public ChiliException
	{
		using ChiliException::ChiliException;
	};
	class HrException : public Exception
	{
	public:
		HrException(int line, const char* file, HRESULT hr, std::vector<std::wstring> infoMsgs = {}) noexcept;
		HrException(int line, const wchar_t* file, HRESULT hr, std::vector<std::wstring> infoMsgs = {}) noexcept;
		const wchar_t* wWhat() const noexcept override;
		const wchar_t* GetType() const noexcept override;
		HRESULT GetErrorCode() const noexcept;
		std::wstring GetErrorString() const noexcept;
		std::wstring GetErrorDescription() const noexcept;
		std::wstring GetErrorInfo() const noexcept;
	private:
		HRESULT hr;
		std::wstring info;
	};
	/*class InfoException : public Exception
	{
	public:
		InfoException(int line, const char* file, std::vector<std::wstring> infoMsgs) noexcept;
		const wchar_t* wWhat() const noexcept override;
		const wchar_t* GetType() const noexcept override;
		std::wstring GetErrorInfo() const noexcept;
	private:
		std::wstring info;
	};*/
	class DeviceRemovedException : public HrException
	{
		using HrException::HrException;
	public:
		const wchar_t* GetType() const noexcept override;
	private:
		std::wstring reason;
	};
	Graphics(HWND hWnd);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics();
	void EndFrame();
	void ClearBuffer(float red, float green, float blue) noexcept;
private:
	ID3D11Device* pDevice = nullptr;
	IDXGISwapChain* pSwapChain = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
	ID3D11RenderTargetView* pTarget;
};

