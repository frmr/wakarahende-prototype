#pragma once

#include <string>
#include <map>
#include <set>
#include <vector>

#include "wkJlpt.hpp"
#include "wkNonKanjiChar.hpp"
#include "wkWord.hpp"
#include "wkKanji.hpp"
#include "wkSet.hpp"

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

		static wk::Set<NonKanjiChar>  loadNonKanji();

	private:
		const wk::Set<NonKanjiChar>   m_nonKanji;
		std::map<KanjiChar, Kanji>    m_kanji;
		std::map<std::wstring, Word>  m_words;

		wk::Set<KanjiChar>            m_startedKanji;
		wk::Set<std::wstring>         m_startedWords;
	};
}