#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>

#include "wkCsvLine.hpp"
#include "wkJlpt.hpp"
#include "wkKanji.hpp"
#include "wkValue.hpp"
#include "wkWordFileField.hpp"
#include "wkNonKanjiChar.hpp"

namespace wk
{
	class Kanji;

	class Word
	{
	public:
		Word(const CsvLine<WordFileField>& csvLine, const Jlpt jlpt, const std::set<NonKanjiChar>& nonKanji, const std::map<KanjiChar, Kanji>& kanjiMap);

		void                       calculateValue();
		bool                       containsKanji(const KanjiChar kanji) const;
		std::set<KanjiChar>        getKanji() const;
		std::set<KanjiChar>        getKanjiNotInSet(const std::set<KanjiChar>& kanjiSet) const;
		Value                      getValue() const;

	private:
		static std::set<KanjiChar> getKanjiFromWord(const std::wstring& word, const std::set<NonKanjiChar>& nonKanji);

	private:
		const std::wstring                m_word;
		const std::wstring                m_hiragana;
		const std::wstring                m_meaning;
		const Jlpt                        m_jlpt;
		const std::set<KanjiChar>         m_wordKanji;
		const std::map<KanjiChar, Kanji>& m_kanjiMap;
		Value                             m_value;
	};
}