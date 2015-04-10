#ifndef __IMGHASH__
#define __IMGHASH__ 1

#include <Windows.h>

#include <string>

bool HashHbitmap(const std::wstring& filePath, std::wstring& pHash);

int32_t HanmingDistance(const std::wstring &a, const  std::wstring &b, uint32_t length = 64);

#endif // !__IMGHASH__
