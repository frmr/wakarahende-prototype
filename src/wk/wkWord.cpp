#include "wkWord.hpp"

wk::Word::Word(const CsvLine<WordFileField>& csvLine, const Jlpt jlpt, const wk::Set<NonKanjiChar>& nonKanji, const std::map<KanjiChar, Kanji>& kanjiMap) :
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
	return m_wordKanji.Contains(kanji);
}

wk::Set<wk::KanjiChar> wk::Word::getKanji() const
{
	return m_wordKanji;
}

wk::Set<wk::KanjiChar> wk::Word::getKanjiNotInSet(const wk::Set<KanjiChar>& kanjiSet) const
{
	wk::Set<KanjiChar> kanjiNotInSet;

	for (const auto& kanji : m_wordKanji)
	{
		if (!kanjiSet.Contains(kanji))
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

wk::Set<wk::KanjiChar> wk::Word::getKanjiFromWord(const std::wstring& word, const wk::Set<NonKanjiChar>& nonKanji)
{
	wk::Set<KanjiChar> wordKanji;

	for (const auto& character : word)
	{
		if (!nonKanji.Contains(character))
		{
			wordKanji.insert(character);
		}
	}

	return wordKanji;
}
