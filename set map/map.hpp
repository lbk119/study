#define _CRT_SECURE_NO_WARNINGS
#include "RBTree.cpp"
namespace lbk
{
	template <class K, class V>
	class map
	{
		struct MapKeyOfT
		{
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};
		typedef typename rbtree::RBTreeIterator<pair<K, V>, pair<K, V>&, pair<K, V>*> iterator;

	public:
		iterator begin()
		{
			return _t.begin();
		}
		iterator end()
		{
			return _t.end();
		}
		pair<iterator, bool> insert(const pair<K, V>& kv)
		{
			return _t.Insert(kv);
		}
		V& operator[](const K& key)
		{
			pair<iterator, bool> ret = insert(make_pair(key, V()));
			return ret.first->second;
		}
		void InOrder()
		{
			_t.InOrder();
		}
	private:
		//前面的K用于传入key的类型，后面的T用于传入红黑树存储的数据类型。
		//红黑树中存储的值不可以改变，应加上const
		rbtree::RBTree<K, const pair<K, V>, MapKeyOfT> _t;
	};
}