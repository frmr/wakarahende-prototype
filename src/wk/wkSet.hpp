#pragma once

#include <set>

namespace wk
{
	template<typename T>
	class Set : public std::set<T>
	{
	public:
		bool Contains(const T& key) const
		{
			return find(key) != end();
		}
	};
}