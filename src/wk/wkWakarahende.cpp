#include "wkWakarahende.hpp"
#include "wkKanjiFile.hpp"
#include "wkNonKanjiFile.hpp"
#include "wkWordFile.hpp"

#include <set>
#include <cassert>

wk::Wakarahende::Wakarahende() :
	m_nonKanji(loadNonKanji())
{
	loadWords();
	buildKanjiMap();

	calculateValues();
}

std::wstring wk::Wakarahende::next()
{
	std::wstring nextWord = calculateNextWord();

	while (nextWord.empty())
	{
		const KanjiChar nextKanji = calculateNextKanji();

		if (nextKanji == L'\0')
		{
			return L"";
		}

		m_startedKanji.insert(nextKanji);
		nextWord = calculateNextWord();
	}

	m_startedWords.insert(nextWord);

	return nextWord;
}

void wk::Wakarahende::buildKanjiMap()
{
	for (const auto& pair : m_words)
	{
		for (const auto character : pair.first)
		{
			if (!m_nonKanji.Contains(character))
			{
				m_kanji.insert({ character, Kanji(character, m_words) });
			}
		}
	}
}

void wk::Wakarahende::calculateKanjiFrequencies()
{
	for (const auto& pair : m_words)
	{
		for (const auto character : pair.first)
		{
			if (!m_nonKanji.Contains(character))
			{
				m_kanji.at(character).incrementFrequency();
			}
		}
	}
}

wk::KanjiChar wk::Wakarahende::calculateNextKanji() const
{
	wk::Set<std::wstring> unstartedWords;

	for (const auto& pair : m_words)
	{
		if (pair.second.getKanjiNotInSet(m_startedKanji).size() == 1)
		{
			unstartedWords.insert(pair.first);
		}
	}

	Value               highestValue = 0;
	KanjiChar           highestValueKanji = L'\0';
	wk::Set<KanjiChar>  checkedKanji;

	for (const auto& word : unstartedWords)
	{
		const KanjiChar unstartedKanji = *(m_words.at(word).getKanjiNotInSet(m_startedKanji).begin());

		Value                 totalValue = 0;
		wk::Set<std::wstring> checkedWords;
		wk::Set<KanjiChar>    combinedKanji;
	
		combinedKanji.insert(m_startedKanji.begin(), m_startedKanji.end());
		combinedKanji.insert(unstartedKanji);

		if (!checkedKanji.Contains(unstartedKanji))
		{
			checkedKanji.insert(unstartedKanji);

			const wk::Set<std::wstring> wordsUsingKanji = m_kanji.at(unstartedKanji).getWordsContainingAllKanji(combinedKanji);

			for (const auto& wordUsingKanji : wordsUsingKanji)
			{
				if (!checkedWords.Contains(wordUsingKanji))
				{
					checkedWords.insert(wordUsingKanji);
					totalValue += m_words.at(wordUsingKanji).getValue();
				}
			}
		}

		if (totalValue > highestValue)
		{
			highestValue = totalValue;
			highestValueKanji = unstartedKanji;
		}
	}

	return highestValueKanji;
}

std::wstring wk::Wakarahende::calculateNextWord() const
{
	wk::Set<std::wstring> startedKanjiWords;

	for (const auto& kanji : m_startedKanji)
	{
		const wk::Set<std::wstring> words = m_kanji.at(kanji).getWords();
		startedKanjiWords.insert(words.begin(), words.end());
	}

	Value        highestValue     = 0.0f;
	std::wstring highestValueWord = L"";

	for (const auto& word : startedKanjiWords)
	{
		if (!m_startedWords.Contains(word) && m_words.at(word).getKanjiNotInSet(m_startedKanji).empty())
		{
			if (m_words.at(word).getValue() > highestValue)
			{
				highestValue = m_words.at(word).getValue();
				highestValueWord = word;
			}
		}
	}

	return highestValueWord;
}

void wk::Wakarahende::calculateWordValues()
{
	for (auto& pair : m_words)
	{
		pair.second.calculateValue();
	}
}

void wk::Wakarahende::calculateKanjiValues()
{
	for (auto& pair : m_kanji)
	{
		pair.second.calculateValue();
	}
}

void wk::Wakarahende::calculateValues()
{
	calculateKanjiFrequencies();
	calculateWordValues();
	calculateKanjiValues();
}

void wk::Wakarahende::loadWords()
{
	const std::map<Jlpt, std::string> wordFiles = {
		{Jlpt::N5, "data/words/n5.csv"},
		{Jlpt::N4, "data/words/n4.csv"},
		{Jlpt::N3, "data/words/n3.csv"}
	};

	for (const auto& pair : wordFiles)
	{
		const WordFile wordFile(pair.second);

		for (const auto& line : wordFile.getLines())
		{
			m_words.insert({line.at(WordFileField::Word), Word(line, pair.first, m_nonKanji, m_kanji)});
		}
	}
}

wk::Set<wk::NonKanjiChar> wk::Wakarahende::loadNonKanji()
{
	const std::vector<std::string> nonKanjiFilenames = {
		"data/kana/hiragana.csv",
		"data/kana/katakana.csv",
		"data/misc/misc.csv"
	};

	wk::Set<NonKanjiChar> nonKanji;

	for (const auto& filename : nonKanjiFilenames)
	{
		NonKanjiFile nonKanjiFile(filename);

		for (const auto& line : nonKanjiFile.getLines())
		{
			const std::wstring fullString = line.at(NonKanjiFileField::Character);

			assert(fullString.size() == 1);

			nonKanji.insert(line.at(NonKanjiFileField::Character).front());
		}
	}

	return nonKanji;
}
