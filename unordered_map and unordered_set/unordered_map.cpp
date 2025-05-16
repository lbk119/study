#define _CRT_SECURE_NO_WARNINGS
#include"HashTable.cpp"
namespace lbk
{
	template<class K, class Hash = OpenHash::Hash<K>>
	class unordered_set
	{
		struct SetKeyOfT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};
	public:
		typedef typename OpenHash::HashTableIterator<K, K, K*, K&, SetKeyOfT, Hash> iterator;
		iterator begin()
		{
			return _ht.begin();
		}
		iterator end()
		{
			return _ht.end();
		}
		iterator find(const K& key)
		{
			return _ht.find(key);
		}
		pair<K, bool> insert(const K& key)
		{
			return _ht.insert(key);
		}
		bool erase(const K& key)
		{
			return _ht.erase(key);
		}
	private:
		OpenHash::HashTable<K, K, SetKeyOfT, Hash> _ht;
	};
}