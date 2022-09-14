#pragma once

#include <Windows.h>

static char	g_UTF8Text[1024] = {};

static char* UTF8(const char* text)
{
	wchar_t		wText[1024] = {}; 
		
	int	Length = MultiByteToWideChar(CP_ACP, 0, text, -1, 0, 0); 
	MultiByteToWideChar(CP_ACP, 0, text, -1, wText, Length);
		
	Length = WideCharToMultiByte(CP_UTF8, 0, wText, -1, 0, 0, 0, 0);
	WideCharToMultiByte(CP_UTF8, 0, wText, -1, g_UTF8Text, Length, 0, 0);

	return g_UTF8Text;
}