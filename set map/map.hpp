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
		//ǰ���K���ڴ���key�����ͣ������T���ڴ��������洢���������͡�
		//������д洢��ֵ�����Ըı䣬Ӧ����const
		rbtree::RBTree<K, const pair<K, V>, MapKeyOfT> _t;
	};
}