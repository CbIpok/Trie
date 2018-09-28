#include <iostream>
#include "Trie.h"
#include "TrieIterator.h"
#include <queue>
using namespace std;

int main()
{
	
	Trie<int> trie;
	trie[""] = -1;
	for (size_t i = 0; i < 20; i++)
	{
		trie[to_string(i)] = i;
	}
	for (size_t i = 15; i < 20; i++)
	{
		trie.erase(to_string(i));
	}
	TrieIterator<int> ti(trie.getMainNode());
	for (size_t i = 0; i < 25; i++)
	{
		try
		{
			cout << *(++ti) << endl;
		}
		catch (const std::out_of_range&)
		{
			cout << "eof" << endl;
		}
		
	}
	return 0;
}