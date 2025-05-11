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
		//ǰ���K���ڴ���key�����ͣ������T���ڴ��������洢���������͡�
		//������д洢��ֵ�����Ըı䣬Ӧ����const
		rbtree::RBTree<K, const K, SetKeyOfT> _t;
	};
};
