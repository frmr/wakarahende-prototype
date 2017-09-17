#pragma once

#include "wkCsvFile.hpp"
#include "wkNonKanjiFileField.hpp"

namespace wk
{
	class NonKanjiFile : public CsvFile<NonKanjiFileField>
	{
	public:
		NonKanjiFile(const std::string& filename) :
			CsvFile(filename, { NonKanjiFileField::Character })
		{
		}
	};
}