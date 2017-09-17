#pragma once

#include <map>
#include <vector>
#include <locale>
#include <fstream>
#include <string>
#include <codecvt>

#include "wkCsvLine.hpp"

namespace wk
{
	template<typename TField>
	class CsvFile
	{
	public:
		CsvFile(const std::string& filename, const std::vector<TField>& fields)
		{
			parse(filename, fields);
		}

		size_t getNumLines() const
		{
			return m_lines.size();
		}
		CsvLine<TField> getLine(const size_t index) const
		{
			return m_lines.at(index);
		}

		std::vector<CsvLine<TField>> getLines() const
		{
			return m_lines;
		}

	private:
		void parse(const std::string& filename, const std::vector<TField>& fields)
		{
			std::wifstream file(filename);
			std::wstring   line;

			file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::little_endian>()));

			while (std::getline(file, line))
			{
				m_lines.emplace_back();

				bool         enclosed = false;
				size_t       fieldIndex = 0;
				std::wstring value;

				for (const auto wideCharacter : line)
				{
					if (wideCharacter == '\"' || wideCharacter == '\'')
					{
						enclosed = !enclosed;
					}
					else if (wideCharacter == ',' && !enclosed)
					{
						m_lines.back().insert({ fields[fieldIndex++], value });
						value.clear();
					}
					else
					{
						value += wideCharacter;
					}
				}

				m_lines.back().insert({ fields[fieldIndex], value });
			}
		}

	private:
		std::vector<CsvLine<TField>> m_lines;
	};
}