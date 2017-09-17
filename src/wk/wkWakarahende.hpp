#pragma once

#include <string>
#include <map>
#include <set>
#include <vector>

#include "wkJlpt.hpp"
#include "wkNonKanjiChar.hpp"
#include "wkWord.hpp"
#include "wkKanji.hpp"

namespace wk
{
	class Wakarahende
	{
	public:
		Wakarahende();

		std::wstring next();

	private:
		void                          buildKanjiMap();
		void                          calculateKanjiFrequencies();
		KanjiChar                     calculateNextKanji() const;
		std::wstring                  calculateNextWord() const;
		void                          calculateWordValues();
		void                          calculateKanjiValues();
		void                          calculateValues();
		void                          loadWords();

		static std::set<NonKanjiChar> loadNonKanji();

	private:
		const std::set<NonKanjiChar> m_nonKanji;
		std::map<KanjiChar, Kanji>   m_kanji;
		std::map<std::wstring, Word> m_words;

		std::set<KanjiChar>          m_startedKanji;
		std::set<std::wstring>       m_startedWords;
	};
}