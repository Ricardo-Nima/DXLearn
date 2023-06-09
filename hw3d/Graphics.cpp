#include "Graphics.h"
#include "dxerr.h"
#include <sstream>


#pragma comment(lib, "d3d11.lib")

Graphics::Graphics(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;
	HRESULT hr;
	//Graphics::HrException(__LINE__, __FILE__, hr);
	GFX_THROW_NOINFO(D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&pSwapChain,
		&pDevice,
		nullptr,
		&pContext
	));
	ID3D11Resource* pBackBuffer = nullptr;
	GFX_THROW_NOINFO(pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&pBackBuffer)));
	GFX_THROW_NOINFO(pDevice->CreateRenderTargetView(
		pBackBuffer,
		nullptr,
		&pTarget
	));
	pBackBuffer->Release();
}

Graphics::~Graphics()
{
	if (pTarget != nullptr) {
		pTarget->Release();
		pTarget = nullptr;
	}
	if (pContext != nullptr) {
		pContext->Release();
		pContext = nullptr;
	}
	if (pSwapChain != nullptr) {
		pSwapChain->Release();
		pSwapChain = nullptr;
	}
	if (pDevice != nullptr) {
		pDevice->Release();
		pDevice = nullptr;
	}	
}

void Graphics::EndFrame()
{
	HRESULT hr;
	if (FAILED(hr = pSwapChain->Present(1u, 0u)))
	{
		if (hr == DXGI_ERROR_DEVICE_REMOVED)
		{
			throw GFX_DEVICE_REMOVED_EXCEPT(pDevice->GetDeviceRemovedReason());
		}
		else
		{
			GFX_THROW_NOINFO(hr);
		}
	}
}

void Graphics::ClearBuffer(float red, float green, float blue) noexcept
{
	const float color[]{ red, green, blue, 1.0f };
	pContext->ClearRenderTargetView(pTarget, color);

}
