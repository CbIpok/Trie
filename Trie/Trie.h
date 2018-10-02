#pragma once
#include <map>
#include<memory>
#include <string>
#include <vector>
#include "TrieIterator.h"

template <class T> class Trie
{
public:

	typedef TrieIterator<T> iterator;
//	typedef ConstTrieIterator<T> const_iterator;

	typedef T value_type;
	typedef std::string key_type;

	struct Node
	{
		Node( Node* parrent = nullptr)
		{
			for (auto& i : childs)
			{
				i = nullptr;
			}
			this->parrent = parrent;
			value.reset(nullptr);
		}
		std::unique_ptr<value_type> value;
		std::unique_ptr<Node> childs[256];
		Node* parrent;
	};

	Trie()
	{
		_trie.reset( new Node());
	}

	
	template <class InputIterator> Trie(InputIterator first, InputIterator last);
	//Trie(const Trie<T> & trie);
	~Trie() = default;

	Trie<T> & operator= (const Trie & trie)
	{
		return Trie<T>(trie);
	}

	iterator begin()
	{
		return iterator(_trie.get());
	}

	//const_iterator begin() const;

	iterator end()
	{
		return iterator();
	}
	//const_iterator end() const;

	
	inline bool empty() const//Test whether container is empty
	{
		return size() == 0;
	}

	inline size_t size() const
	{
		return _size;
	}

	const value_type& operator[] (const key_type& k) const
	{
		return _getNode(k).first.value;
	}

	value_type& operator[] (const key_type& k)
	{
		Node& node = _getNode(k).first;
		if (node.value.get() == nullptr)
		{
			node.value.reset(new value_type);
		}
		return *node.value.get();
	}
	
	std::pair<iterator, bool> insert(const key_type& k, const value_type& val)//NOT TESTED
	{
		auto node = _getNode(k);
		node.first.value = val;
		return std::pair<iterator, bool>(node.first,node.second);
	}

	//template <class InputIterator> void insert(InputIterator first, InputIterator last);

	//удаление
	void erase(iterator position)
	{
		erase((*position).first);
	}

	size_t erase(const key_type& k)
	{
		if (!_findNode(k))
		{
			return 0;
		}
		else
		{
			delete(_getNode(k).first.value.release());
			_getNode(k).first.value.reset(nullptr); 
			_size--;
			return 1;
		}
	}

	void erase(iterator first, iterator last)
	{
		for (; (first != last) && (first!= end()); first++)
		{
			erase((*first).first);
		}
	}

	//void swap(Trie& trie);

	void clear()
	{
		
	}

	//найти элемент
	iterator find(const key_type& k) //НЕ РАБОТАЕТ
	{
		if (!_findNode(k))
		{
			throw std::out_of_range("");
		}
		return iterator(&_getNode(k).first);
	}
	//const_iterator find(const key_type& k) const;

	//SubTrie<T> GetSubTrie(const key_type & subKey); // получить subtree

	inline Node* getMainNode() { return _trie.get(); };
private:
	size_t _size = 0;
	std::unique_ptr<Node> _trie;

protected:
	std::pair<Node&,bool> _getNode(const key_type& k)
	{
		Node* curNode = _trie.get();
		bool isCreated = false;
		for (size_t i = 0; i < k.size(); i++)
		{
			unsigned char index = (k.at(i));
			if (curNode->childs[index].get() != nullptr)
			{
				curNode = curNode->childs[index].get();
			}
			else
			{
				curNode->childs[index].reset(new Node(curNode));
				curNode = curNode->childs[index].get();
				isCreated = true;
			}
		}

		return std::pair<Node&, bool>(*curNode,isCreated);
	}

	bool _findNode(const key_type& k)
	{
		Node* curNode = _trie.get();
		for (size_t i = 0; i < k.size(); i++)
		{
			unsigned char index = (k.at(i));
			if (curNode->childs[index].get() != nullptr)
			{
				curNode = curNode->childs[index].get();
			}
			else
			{
				return false;
			}
		}
		return curNode->value.get() != nullptr;
	}
	
};