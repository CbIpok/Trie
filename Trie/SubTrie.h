#pragma once
#include "Trie.h"
#include "TrieIterator.h"
template <class T> class SubTrie : public SubTrie<T>
{
public:
	using node = typename Trie<T>::Node;
	
private:
	size_t _size = 0;
	node& _trie;
};