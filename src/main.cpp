#include "wk/wkWakarahende.hpp"

#include <cassert>
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

	std::set<std::wstring> seen;

	for (int i = 0; i < 5000; ++i)
	{
		const std::wstring next = app.next();

		if (seen.find(next) != seen.end())
		{
			std::cout << "ERROR: ";
			print(next);
			return 1;
		}

		seen.insert(next);
		print(next);
	}

	return 0;
}