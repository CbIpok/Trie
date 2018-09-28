#include <iostream>
#include "Trie.h"
#include "TrieIterator.h"
#include <queue>
using namespace std;

int main()
{
	
	Trie<int> trie;
	trie[""] = -1;
	for (size_t i = 1; i < 50; i++)
	{
		trie[to_string(i)] = i;
	}
	TrieIterator<int> ti(trie.getMainNode());
	for (size_t i = 0; i < 100; i++)
	{
		cout << *(++ti)<<endl;
	}
	return 0;
}