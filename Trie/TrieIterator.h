#pragma once
#include "Trie.h"
#include <queue>
template <class T> class TrieIterator : public std::iterator<std::forward_iterator_tag, std::pair<std::string, T&>>
{
public:
	TrieIterator(const Trie& x)
	{

	}
	TrieIterator(const TrieIterator& mit);

	TrieIterator& operator++();
	TrieIterator operator++(int);

	bool operator==(const TrieIterator& rhs);
	bool operator!=(const TrieIterator& rhs);

	value_type operator*();
	value_type * operator->();
private:
	const Trie& _trie;

};