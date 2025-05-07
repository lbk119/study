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
	//��keyת��Ϊ���ͷ���ȡģ
	template <class K>
	class Hash
	{
		size_t operator()(const K& key)
		{
			return key;
		}
	};
	//ģ���ػ�,��string����ת��Ϊ����
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
	//ʵ�ֵ�����
	//��Ϊ��������ʵ����Ҫ����HashTable��������Ҫǰ�ö���
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
			//������ǰͰ
			if (_node->_next)
				_node = _node->_next;
			//����һ��Ͱ
			else
			{
				KeyOfT kot;
				HashFunc hf;
				//��ȡ����ֵ
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
		//��Ԫ(��Ϊiterator��Ҫ�õ�_table)
		template <class K, class T, class Ptr, class Ref, class KeyOfT, class HashFunc>
		friend struct HashTableIterator;
	private:
		vector<Node*> _table;
		size_t _n;//��Ч���ݸ���
	public:
		//���캯��
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
			//��һ�β�����Ҫ����
			if (_table.size() == 0)
				_table.resize(10);
			//���ܳ����ظ�����
			if (find(key) != iterator(nullptr, this))
			{
				return make_pair(find(key), false);
			}
			KeyOfT kot;
			HashFunc hf;
			//Ͱ�ĸ�����һ���ģ�����Ԫ�صĲ��ϲ��룬ÿ��Ͱ��Ԫ�صĸ����������࣬��������£�
			//���ܻᵼ��һ��Ͱ������ڵ�ǳ��࣬��Ӱ��Ĺ�ϣ������ܣ������һ����������Ҫ��
			//��ϣ��������ݣ��Ǹ�������ôȷ���أ���ɢ����õ�����ǣ�ÿ����ϣͰ�иպù�һ��
			//�ڵ�,�ټ�������Ԫ��ʱ��ÿһ�ζ��ᷢ����ϣ��ͻ����ˣ���Ԫ�ظ����պõ���Ͱ�ĸ���
			//ʱ�����Ը���ϣ�����ݡ�
			//�������ӵ�1����Ҫ����
			if (_n == _table.size())
			{
				vector<Node*> newtable;
				newtable.resize(_table.size() * 2);
				//����ӳ�䵽�±�
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
					//Ҫɾ����λ�õ�һ��Ԫ��
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