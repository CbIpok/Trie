#include <iostream>
#include "Trie.h"
using namespace std;

int main()
{
	Trie<int>  trie;
	trie["�"] = 5;
	cout << trie["�"]<<endl;
	int a = 5;
	return 0;
}