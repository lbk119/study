//#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
using namespace std;
namespace OpenHash
{
	template<class T>
	struct HashNode
	{
		T _data;
		HashNode* _next;
		HashNode(const T& data)
			:_data(data)
			, _next(nullptr)
		{}
	};
	//将key转换为整型方便取模
	template <class K>
	class Hash
	{
		size_t operator()(const K& key)
		{
			return key;
		}
	};
	//模板特化,将string类型转换为整型
	template<>
	class Hash<string>
	{
		size_t operator()(const string& s)
		{
			size_t ret = 0;
			for (auto e : s)
			{
				ret = ret * 31 + e;
			}
			return ret;
		}
	};
	//实现迭代器
	//因为迭代器的实现需要借助HashTable，所以需要前置定义
	template <class K, class T, class KeyOfT, class HashFunc = Hash<K>>
	class HashTable;
	template <class K, class T, class Ptr, class Ref, class KeyOfT, class HashFunc = Hash<K>>
	struct HashTableIterator
	{
		typedef HashNode<T> Node;
		typedef HashTableIterator<K, T, Ptr, Ref, KeyOfT, HashFunc> Self;
		typedef HashTable<K, T, KeyOfT, HashFunc> HashTable;

		HashTable* _ht;
		Node* _node;
		HashTableIterator(const Node*& node, const HashTable*& ht)
			:_ht(ht)
			, _node(node)
		{}
		Self& operator++()
		{
			//遍历当前桶
			if (_node->_next)
				_node = _node->_next;
			//找下一个桶
			else
			{
				KeyOfT kot;
				HashFunc hf;
				//获取索引值
				size_t index = hf(kot(_node->_data)) % _ht->_table.size();
				++index;
				while (index < _ht->_table.size() && _ht->_table[index] == nullptr)
					++index;
				if (index == _ht->_table.size())
					_node = nullptr;
				else
					_node = _ht->_table[index];
			}
			return *this;
		}
		Ref operator*()
		{
			return _node->_data;
		}
		Ptr operator->()
		{
			return &_node->_data;
		}
		bool operator==(const Self& s)
		{
			return _node == s._node;
		}
		bool operator!=(const Self& s)
		{
			return _node != s._node;
		}
	};

	template <class K, class T, class KeyOfT, class HashFunc>
	class HashTable
	{
		typedef HashNode<T> Node;
		typedef HashTableIterator<K, T, T*, T&, KeyOfT, HashFunc> iterator;
		//友元(因为iterator需要用到_table)
		template <class K, class T, class Ptr, class Ref, class KeyOfT, class HashFunc>
		friend struct HashTableIterator;
	private:
		vector<Node*> _table;
		size_t _n;//有效数据个数
	public:
		//构造函数
		HashTable()
			:_table(vector<Node*>())
			, _n(0)
		{}
		iterator begin()
		{
			for (size_t i = 0; i < _table.size(); i++)
			{
				if (_table[i])
					return iterator(_table[i], this);
			}
			return iterator(nullptr, this);
		}
		iterator end()
		{
			return iterator(nullptr, this);
		}
		iterator find(const K& key)
		{
			if (_table.size() == 0)
			{
				return iterator(nullptr, this);
			}
			KeyOfT kot;
			HashFunc hf;
			size_t index = hf(key) % _table.size();
			Node* cur = _table[index];
			while (cur)
			{
				if (kot(cur->_data) == key)
					return iterator(cur, this);
				cur = cur->_next;
			}
			return iterator(nullptr, this);
		}
		pair<iterator, bool> insert(const K& key)
		{
			//第一次插入需要扩容
			if (_table.size() == 0)
				_table.resize(10);
			//不能出现重复数据
			if (find(key) != iterator(nullptr, this))
			{
				return make_pair(find(key), false);
			}
			KeyOfT kot;
			HashFunc hf;
			//桶的个数是一定的，随着元素的不断插入，每个桶中元素的个数不断增多，极端情况下，
			//可能会导致一个桶中链表节点非常多，会影响的哈希表的性能，因此在一定条件下需要对
			//哈希表进行增容，那该条件怎么确认呢？开散列最好的情况是：每个哈希桶中刚好挂一个
			//节点,再继续插入元素时，每一次都会发生哈希冲突，因此，在元素个数刚好等于桶的个数
			//时，可以给哈希表增容。
			//负载因子到1，需要扩容
			if (_n == _table.size())
			{
				vector<Node*> newtable;
				newtable.resize(_table.size() * 2);
				//重新映射到新表
				for (auto e : _table)
				{
					Node* cur = e;
					while (cur)
					{
						size_t index = hf(kot(cur->_data)) % newtable.size();
						cur->_next = newtable[index];
						newtable[index] = cur;
						cur = cur->_next;
					}
				}
			}
			size_t index = hf(key) % _table.size();
			Node*& cur = _table[index];
			while (cur)
				cur = cur->_next;
			cur = new Node(key);
			return make_pair(iterator(cur, this), true);
		}
		bool erase(const K& key)
		{
			KeyOfT kot;
			HashFunc hf;
			size_t index = hf(key) % _table.size();
			Node* cur = _table[index], * pre = _table[index];
			while (cur)
			{
				if (kot(cur->_data) == key)
				{
					//要删除该位置第一个元素
					if (cur == pre)
						_table[index] = cur->_next;
					else
						pre->_next = cur->_next;

					delete cur;
					_n--;
					return true;
				}
				pre = cur;
				cur = cur->_next;
			}
			return false;
		}
	};
}