#include <iostream>
#include "Trie.h"
#include "TrieIterator.h"
#include <queue>
using namespace std;

int main()
{
	
	Trie<int> trie;
	trie[""] = -1;
	for (size_t i = 0; i < 100; i++)
	{
		trie[to_string(i)] = i;
	}
	TrieIterator<int> ti(trie.getMainNode());
	cout << *ti;
	return 0;
}