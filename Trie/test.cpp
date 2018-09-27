#include <iostream>
#include "Trie.h"
using namespace std;

int main()
{
	Trie<int>  trie;
	trie["ÿ"] = 5;
	cout << trie["ÿ"]<<endl;
	int a = 5;
	return 0;
}