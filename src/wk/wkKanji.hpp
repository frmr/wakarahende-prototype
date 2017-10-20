#pragma once

#include <map>
#include <string>

#include "wkJlpt.hpp"
#include "wkKanjiChar.hpp"
#include "wkValue.hpp"
#include "wkWord.hpp"
#include "wkSet.hpp"

namespace wk
{
	class Word;

	class Kanji
	{
	public:
		Kanji(const KanjiChar kanji, const std::map<std::wstring, Word>& wordMap);

		void                                calculateValue();
		int                                 getFrequency() const;
		wk::Set<std::wstring>               getWords() const;
		wk::Set<std::wstring>               getWordsContainingAllKanji(const wk::Set<KanjiChar>& kanjiList) const;
		void                                incrementFrequency();

	private:
		static wk::Set<std::wstring>        getWordsContainingKanji(const KanjiChar kanji, const std::map<std::wstring, Word>& wordMap);

	private:
		const KanjiChar                     m_kanji;
		const std::map<std::wstring, Word>& m_wordMap;
		const wk::Set<std::wstring>         m_words;
		int                                 m_frequency;
		Value                               m_value;
	};
}