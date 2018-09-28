#pragma once
#include "Trie.h"
#include <queue>
template <class T> class TrieIterator : public std::iterator<std::forward_iterator_tag, std::pair<std::string, T&>>
{
public:
	using value_type = T;
	using value_type_trie = Trie<value_type>;
	using node = typename value_type_trie::Node;
	TrieIterator(node* x)
	{
		_curNode = x;
	}
	TrieIterator(const TrieIterator& mit);

	TrieIterator& operator++()
	{
		
	}
	TrieIterator operator++(int);

	bool operator==(const TrieIterator& rhs);
	bool operator!=(const TrieIterator& rhs);

	value_type operator*()
	{
		return  *_curNode->value.get();
	}
	value_type * operator->();
private:
	std::queue<char> _trieTrace;
	node* _curNode;

};