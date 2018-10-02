#pragma once
#include "Trie.h"
#include "StringStack.h"
#include <map>
#include <string>
//#include <stack>
template <class T> class Trie;

template <class T> class TrieIterator : public std::iterator<std::forward_iterator_tag, std::pair<std::string, T&>> 
{
public:
	using value_type = T;
	using value_type_trie = Trie<value_type>;
	using node = typename value_type_trie::Node;
	TrieIterator(node* x)
	{
		_curNode = x;
		if (_curNode->value == nullptr)
		{
			(*this)++;
		}
	}
	TrieIterator()
	{
		_curNode = nullptr;
	}

	virtual ~TrieIterator() = default;
	//TrieIterator(const TrieIterator& mit);


	TrieIterator& operator++()
	{
		try
		{
			do
			{
				_getNextNode();
			} while (_curNode->value.get() == nullptr);
		}
		catch (const std::out_of_range)
		{

		}
		
		
		return *this;
	}

	TrieIterator operator++(int)
	{
		TrieIterator trieIterator(*this);
		++(*this);
		return trieIterator;
	}

	inline bool operator==(const TrieIterator& rhs)
	{
		return _curNode == rhs.getNode();
	}
	inline bool operator!=(const TrieIterator& rhs)
	{
		return !(_curNode == rhs.getNode());
	}

	std::pair<std::string, T*> operator*()
	{
		return  std::pair<std::string, T*>(_trieTrace.getString(), (_curNode == nullptr) ? nullptr : _curNode->value.get());
	}

	value_type * operator->()
	{
		_curNode->value;
	}
	
	inline const node* getNode() const { return _curNode; };
protected:
	

	bool _getFirstIndex(unsigned char& index, unsigned char startPos = 0)
	{
		for (unsigned char i = startPos + 1; i < UCHAR_MAX; i++)
		{
			if (_curNode->childs[i].get() != nullptr)
			{
				index = i;
				return true;
			}
		}
		return false;
	}

	
	node* _getNextNode(bool isFallingDown = true)
	{
		if (_curNode == nullptr)
		{
			throw(std::out_of_range("can not iterate eof"));
		}
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
			while (!_getFirstIndex(index, _trieTrace.top()))
			{
				_trieTrace.pop();
				_curNode = _curNode->parrent;
				if (_curNode == nullptr)
				{
					throw(std::out_of_range("can not iterate eof"));
				}
			}

			_trieTrace.pop();
			_curNode = _curNode->childs[index].get();
			_trieTrace.push(index);

			return _curNode;
		}

	}

	private:
		StringStack _trieTrace;
		node* _curNode;
};