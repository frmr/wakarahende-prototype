#include "wkKanji.hpp"

wk::Kanji::Kanji(const KanjiChar kanji, const std::map<std::wstring, Word>& wordMap) :
	m_kanji(kanji),
	m_wordMap(wordMap),
	m_words(getWordsContainingKanji(kanji, wordMap)),
	m_frequency(0),
	m_value(0)
{
}

void wk::Kanji::calculateValue()
{
	for (const auto& word : m_words)
	{
		m_value += m_wordMap.at(word).getValue();
	}

	m_value /= (m_words.size() * m_words.size());
}

int wk::Kanji::getFrequency() const
{
	return m_frequency;
}

wk::Set<std::wstring> wk::Kanji::getWords() const
{
	return m_words;
}

wk::Set<std::wstring> wk::Kanji::getWordsContainingAllKanji(const wk::Set<KanjiChar>& kanjiList) const
{
	wk::Set<std::wstring> wordsUsingKanji;

	for (const auto& word : m_words)
	{
		if (m_wordMap.at(word).getKanjiNotInSet(kanjiList).empty())
		{
			wordsUsingKanji.insert(word);
		}
	}

	return wordsUsingKanji;
}

void wk::Kanji::incrementFrequency()
{
	++m_frequency;
}

wk::Set<std::wstring> wk::Kanji::getWordsContainingKanji(const KanjiChar kanji, const std::map<std::wstring, Word>& wordMap)
{
	wk::Set<std::wstring> words;

	for (const auto& pair : wordMap)
	{
		if (pair.second.containsKanji(kanji))
		{
			words.insert(pair.first);
		}
	}

	return words;
}
