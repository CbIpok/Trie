#include <iostream>
#include "Trie.h"
#include "TrieIterator.h"
#include <queue>
using namespace std;

int main()
{
	
	Trie<int> trie;
	trie[""] = -1;
	for (size_t i = 0; i < 10; i++)
	{
		trie[to_string(i)] = i;
	}
	
	auto ti = trie.find("5");
	
	while (ti!=trie.end())
	{
		cout << (*ti++).first << " " << (*ti).second << endl;
	}
	/*for (const auto &i : trie)
	{
		cout << i.first << " " << *i.second << endl;
	}*/
	return 0;
}