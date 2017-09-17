#pragma once

#include <map>
#include <string>

#include "wkJlpt.hpp"
#include "wkKanjiChar.hpp"
#include "wkValue.hpp"
#include "wkWord.hpp"

namespace wk
{
	class Word;

	class Kanji
	{
	public:
		Kanji(const KanjiChar kanji, const std::map<std::wstring, Word>& wordMap);

		void                   calculateValue();
		int                    getFrequency() const;
		std::set<std::wstring> getWords() const;
		std::set<std::wstring> getWordsUsingKanji(const std::set<KanjiChar>& kanjiList) const;
		void                   incrementFrequency();

	private:
		static std::set<std::wstring> getWordsContainingKanji(const KanjiChar kanji, const std::map<std::wstring, Word>& wordMap);

	private:
		const KanjiChar                     m_kanji;
		const std::map<std::wstring, Word>& m_wordMap;
		const std::set<std::wstring>        m_words;
		int                                 m_frequency;
		Value                               m_value;
	};
}