#include "wkWord.hpp"

wk::Word::Word(const CsvLine<WordFileField>& csvLine, const Jlpt jlpt, const std::set<NonKanjiChar>& nonKanji, const std::map<KanjiChar, Kanji>& kanjiMap) :
	m_word(csvLine.at(WordFileField::Word)),
	m_hiragana(csvLine.at(WordFileField::Hiragana)),
	m_meaning(csvLine.at(WordFileField::Meaning)),
	m_jlpt(jlpt),
	m_wordKanji(getKanjiFromWord(m_word, nonKanji)),
	m_kanjiMap(kanjiMap),
	m_value(0.0f)
{
}

void wk::Word::calculateValue()
{
	for (const auto& kanji : m_wordKanji)
	{
		m_value += float(m_kanjiMap.at(kanji).getFrequency());
	}

	m_value /= (m_wordKanji.size() * m_wordKanji.size());
}

bool wk::Word::containsKanji(const KanjiChar kanji) const
{
	return m_wordKanji.find(kanji) != m_wordKanji.end();
}

std::set<wk::KanjiChar> wk::Word::getKanji() const
{
	return m_wordKanji;
}

std::set<wk::KanjiChar> wk::Word::getKanjiNotInSet(const std::set<KanjiChar>& kanjiSet) const
{
	std::set<KanjiChar> kanjiNotInSet;

	for (const auto& kanji : m_wordKanji)
	{
		if (kanjiSet.find(kanji) == kanjiSet.end())
		{
			kanjiNotInSet.insert(kanji);
		}
	}

	return kanjiNotInSet;
}

wk::Value wk::Word::getValue() const
{
	return m_value;
}

std::set<wk::KanjiChar> wk::Word::getKanjiFromWord(const std::wstring& word, const std::set<NonKanjiChar>& nonKanji)
{
	std::set<KanjiChar> wordKanji;

	for (const auto& character : word)
	{
		if (nonKanji.find(character) == nonKanji.end())
		{
			wordKanji.insert(character);
		}
	}

	return wordKanji;
}
