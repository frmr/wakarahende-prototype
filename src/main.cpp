#include "wk/wkWakarahende.hpp"

#include <codecvt>
#include <iostream>
#include <locale>
#include <Windows.h>

void print(const std::wstring& string)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

	SetConsoleOutputCP(CP_UTF8);
	std::cout << converter.to_bytes(string) << std::endl;
}

int main()
{
	wk::Wakarahende app;

	for (int i = 0; i < 500; ++i)
	{
		const std::wstring next = app.next();
		print(next);
	}

	return 0;
}