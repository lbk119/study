#define _CRT_SECURE_NO_WARNINGS
#include "RBTree.cpp"
namespace lbk
{
	template<class K>
	class set
	{
		struct SetKeyOfT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};
	public:
		typedef typename rbtree::RBTreeIterator<K, K&, K*> iterator;
		iterator begin()
		{
			return _t.begin();
		}
		iterator end()
		{
			return _t.end();
		}
		pair<iterator, bool> insert(const K& key)
		{
			return _t.Insert(key);
		}
		void InOrder()
		{
			_t.InOrder();
		}
	private:
		//前面的K用于传入key的类型，后面的T用于传入红黑树存储的数据类型。
		//红黑树中存储的值不可以改变，应加上const
		rbtree::RBTree<K, const K, SetKeyOfT> _t;
	};
};
