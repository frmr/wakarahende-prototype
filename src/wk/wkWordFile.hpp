#pragma once

#include "wkCsvFile.hpp"
#include "wkWordFileField.hpp"

namespace wk
{
	class WordFile : public CsvFile<WordFileField>
	{
	public:
		WordFile(const std::string& filename) :
			CsvFile(filename, { WordFileField::Word, WordFileField::Hiragana, WordFileField::Meaning })
		{
		}
	};
}