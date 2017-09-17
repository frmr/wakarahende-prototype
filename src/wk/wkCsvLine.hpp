#pragma once

#include <map>
#include <string>

namespace wk
{
	template<typename TField>
	using CsvLine = std::map<TField, std::wstring>;
}