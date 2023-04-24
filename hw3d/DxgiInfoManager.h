#pragma once
#include "ChiliWin.h"
#include <vector>
#include <dxgidebug.h>
#include <string>

class DxgiInfoManager
{
public:
	DxgiInfoManager();
	~DxgiInfoManager();
	DxgiInfoManager(const DxgiInfoManager&) = delete;
	DxgiInfoManager& operator=(const DxgiInfoManager&) = delete;
	void Set() noexcept;
	std::vector<std::wstring> GetMessages() const;
private:
	unsigned long long next = 0u;
	IDXGIInfoQueue* pDxgiInfoQueue = nullptr;
};
