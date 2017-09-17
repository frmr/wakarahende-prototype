#pragma once

#include "wkCsvFile.hpp"
#include "wkKanjiFileField.hpp"

namespace wk
{
	class KanjiFile : public CsvFile<KanjiFileField>
	{
	public:
		KanjiFile(const std::string& filename) :
			CsvFile(filename, { KanjiFileField::Kanji, KanjiFileField::On, KanjiFileField::Kun, KanjiFileField::Meaning })
		{
		}
	};
}