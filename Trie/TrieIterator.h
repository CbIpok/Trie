#pragma once
#include "Trie.h"
#include <stack>
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
		_getNextNode();
		return *this;
	}

	/*TrieIterator operator++(int)
	{

	}*/

	bool operator==(const TrieIterator& rhs);
	bool operator!=(const TrieIterator& rhs);

	value_type operator*()
	{
		return  *_curNode->value.get();
	}
	value_type * operator->();
private:
	std::stack<char> _trieTrace;
	node* _curNode;

	bool _getFirstIndex (unsigned char& index,unsigned char startPos = 0)
	{
		for (unsigned char i = startPos + 1; i < UCHAR_MAX; i++)
		{
			if (_curNode->childs[i].get()!=nullptr)
			{
				index = i;
				return true;
			}
		}
		return false;
	}
	node* _getNextNode(bool isFallingDown = true)
	{
		unsigned char index;
		if (isFallingDown)
		{
			if (_getFirstIndex(index))
			{
				_curNode = _curNode->childs[index].get();
				_trieTrace.push(index);
				return _curNode;
			}
			else if (_curNode->parrent != nullptr)
			{
				return _getNextNode(false);
			}
		}
		else
		{
			_curNode = _curNode->parrent;
			try
			{
				while (!_getFirstIndex(index, _trieTrace.top()))
				{
					_trieTrace.pop();
					_curNode = _curNode->parrent;
				}
			}
			catch (const std::exception&)
			{
				throw(std::out_of_range("can't iterate eof"));
			}
			_trieTrace.pop();
			_curNode = _curNode->childs[index].get();
			_trieTrace.push(index);
		
			return _curNode;
		}

	}
};