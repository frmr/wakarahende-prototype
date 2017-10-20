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
#include "wkSet.hpp"

namespace wk
{
	class Kanji;

	class Word
	{
	public:
		Word(const CsvLine<WordFileField>& csvLine, const Jlpt jlpt, const wk::Set<NonKanjiChar>& nonKanji, const std::map<KanjiChar, Kanji>& kanjiMap);

		void                              calculateValue();
		bool                              containsKanji(const KanjiChar kanji) const;
		wk::Set<KanjiChar>                getKanji() const;
		wk::Set<KanjiChar>                getKanjiNotInSet(const wk::Set<KanjiChar>& kanjiSet) const;
		Value                             getValue() const;

	private:
		static wk::Set<KanjiChar>         getKanjiFromWord(const std::wstring& word, const wk::Set<NonKanjiChar>& nonKanji);

	private:
		const std::wstring                m_word;
		const std::wstring                m_hiragana;
		const std::wstring                m_meaning;
		const Jlpt                        m_jlpt;
		const wk::Set<KanjiChar>          m_wordKanji;
		const std::map<KanjiChar, Kanji>& m_kanjiMap;
		Value                             m_value;
	};
}