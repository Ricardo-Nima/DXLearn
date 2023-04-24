#pragma once
#include <string>
#include "ChiliWin.h"
#include <memory>

//Converting a WChar string to a Ansi string
class StringConverter
{
public:
    static std::string ws2s(const std::wstring& inputws)
    {
        return WChar2Ansi(inputws.c_str());
    }
    static std::wstring s2ws(const std::string& s)
    {
        return Ansi2WChar(s.c_str(), s.size());
    }

private:
    static std::string WChar2Ansi(LPCWSTR pwszSrc)
    {
        int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
        if (nLen <= 0) 
            return std::string("");
        std::unique_ptr<char[]> pChar = std::make_unique<char[]>(nLen);
        if (NULL == pChar) 
            return std::string("");
        WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pChar.get(), nLen, NULL, NULL);
        pChar[nLen - 1] = 0;
        std::string strTemp(pChar.get());
        return strTemp;
    }
    static std::wstring Ansi2WChar(LPCSTR pszSrc, int nLen)
    {
        int nSize = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pszSrc, nLen, 0, 0);
        if (nSize <= 0) return std::wstring();

        WCHAR* pwszDst = new WCHAR[nSize + 1];
        if (NULL == pwszDst) return std::wstring();

        MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pszSrc, nLen, pwszDst, nSize);
        pwszDst[nSize] = 0;


        //TODO: use memory move
        if (pwszDst[0] == 0xFEFF)                    // skip Oxfeff
            for (int i = 0; i < nSize; i++)
                pwszDst[i] = pwszDst[i + 1];

        std::wstring wcharString(pwszDst);
        delete[] pwszDst;

        return wcharString;
    }
};