#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;
namespace rbtree
{
	enum Color
	{
		RED,
		BLACK,
	};
	//��������Ҫ�洢��ֵ�ԣ���ôT����pair<K, V>
	//������ֻ�洢keyֵ����ôT����K
	template <class T>
	struct RBTreeNode
	{
		//���캯��
		RBTreeNode(T data)
			:_left(nullptr)
			, _right(nullptr)
			, _parent(nullptr)
			, _data(data)
			, _col(RED)
		{}
		//��Ա����
		RBTreeNode* _left;
		RBTreeNode* _right;
		RBTreeNode* _parent;
		T _data;//�ڵ�����
		Color _col;//��ɫ
	};
	//ʵ�ֵ�����
	template<class T, class Ref, class Ptr>
	struct RBTreeIterator
	{
		typedef RBTreeNode<T> Node;
		typedef RBTreeIterator<T, Ref, Ptr> Self;
		Node* _node;
		//���캯��
		RBTreeIterator(Node* node)
			:_node(node)
		{}
		Ref operator*()
		{
			return _node->_data;
		}
		Ptr operator->()
		{
			return &(_node->_data);
		}
		bool operator==(const Self& s)const
		{
			return _node == s._node;
		}
		bool operator!=(const Self& s)const
		{
			return _node != s._node;
		}
		//ǰ��++
		Self& operator++()
		{
			//�����������Ϊ�գ�˵������δȡ�꣬Ҫȡ��������������
			if (_node->_right)
			{
				Node* left = _node->_right;
				while (left->_left)
				{
					left = left->_left;
				}
				_node = left;
			}
			//������Ϊ�գ�˵�������Ѿ�ȡ�꣬Ҫ�ص�curΪ���ӵ�parent
			else
			{
				Node* cur = _node, * parent = cur->_parent;
				while (parent && parent->_right == cur)
				{
					cur = parent;
					parent = cur->_parent;
				}
				_node = parent;
			}
			return *this;
		}
		//����++
		Self operator++(int)
		{
			Self old = new Self(_node);
			//�����������Ϊ�գ�˵������δȡ�꣬Ҫȡ��������������
			if (_node->_right)
			{
				Node* left = _node->_right;
				while (left->_left)
				{
					left = left->_left;
				}
				_node = left;
			}
			//������Ϊ�գ�˵�������Ѿ�ȡ�꣬Ҫ�ص�curΪ���ӵ�parent
			else
			{
				Node* cur = _node, * parent = cur->_parent;
				while (parent && parent->_right == cur)
				{
					cur = parent;
					parent = cur->_parent;
				}
				_node = parent;
			}
			return old;
		}
		//ǰ��--
		Self& operator--()
		{
			Self old = new Self(_node);
			//�����������Ϊ�գ�˵������δȡ�꣬Ҫȡ�����������ҽ��
			if (_node->_left)
			{
				Node* right = _node->_left;
				while (right->_right)
				{
					right = right->_right;
				}
				_node = right;
			}
			//������Ϊ�գ�˵�������Ѿ�ȡ�꣬Ҫ�ص�curΪ�Һ��ӵ�parent
			else
			{
				Node* cur = _node, * parent = cur->_parent;
				while (parent && parent->_left == cur)
				{
					cur = parent;
					parent = cur->_parent;
				}
				_node = parent;
			}
			return old;
		}
		//����--
		Self operator--(int)
		{
			//�����������Ϊ�գ�˵������δȡ�꣬Ҫȡ�����������ҽ��
			if (_node->_left)
			{
				Node* right = _node->_left;
				while (right->_right)
				{
					right = right->_right;
				}
				_node = right;
			}
			//������Ϊ�գ�˵�������Ѿ�ȡ�꣬Ҫ�ص�curΪ�Һ��ӵ�parent
			else
			{
				Node* cur = _node, * parent = cur->_parent;
				while (parent && parent->_left == cur)
				{
					cur = parent;
					parent = cur->_parent;
				}
				_node = parent;
			}
			return *this;
		}
	};
	//ǰ���K���ڴ���key�����ͣ������T���ڴ��������洢���������͡�
	////keyOfT�º�����ȡ��T�����е�key,���ڱȽ�
	template<class K, class T, class KeyOfT>
	class RBTree
	{
		typedef typename RBTreeNode<T> Node;
		typedef typename RBTreeIterator<T, T&, T*> iterator;
	public:
		//���캯��
		RBTree()
			:_root(nullptr)
		{} 
		//��������
		~RBTree()
		{
			Destroy(_root);
			_root = nullptr;
		}
		iterator begin()
		{
			Node* left = _root;
			while (left->_left)
			{
				left = left->_left;
			}
			return iterator(left);
		}
		iterator end()
		{
			return iterator(nullptr);
		}

		pair<iterator, bool> Insert(const T& data)
		{
			KeyOfT kot; 
			if (_root == nullptr)
			{
				_root = new Node(data);
				_root->_col = BLACK;
				return make_pair(iterator(_root), true);
			}
			//��λ�ò���
			Node* cur = _root, * parent = _root;
			while (cur)
			{
				if (kot(data) < kot(cur->_data))
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (kot(data) > kot(cur->_data))
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					return make_pair(iterator(cur), false);
				}
			}
			cur = new Node(data);
			cur->_parent = parent;
			if (kot(data) < kot(parent->_data))
			{
				parent->_left = cur;
			}
			else
			{
				parent->_right = cur;
			}
			Node* ret = cur;
			//�����ɫ(����������������ɫʱ��Ҫ����)
			while (parent && parent->_col == RED)
			{
				Node* grandparent = parent->_parent;
				if (parent == grandparent->_left)
				{
					Node* uncle = grandparent->_right;
					//���uncle������Ϊ�죬��parent��uncle��ڣ�grandparent���
					if (uncle && uncle->_col == RED)
					{
						parent->_col = uncle->_col = BLACK;
						grandparent->_col = RED;
						//�������ϼ��
						cur = grandparent;
						parent = cur->_parent;
					}
					//uncle�����ڻ���Ϊ��
					else
					{
						//��grandparent������grandparent��Ϊ��,parent��Ϊ��
						if (cur == parent->_left)
						{
							RotateR(grandparent);
							grandparent->_col = RED;
							parent->_col = BLACK;
						}
						//��parent������grandparent��������cur��Ϊ�ڣ�grandparent��Ϊ��
						else
						{
							RotateL(parent);
							RotateR(grandparent);
							grandparent->_col =  RED;
							cur->_col = BLACK;
						}
						//��ʱ������Ľ��Ϊ�ڣ�����ֱ�ӽ���
						break;
					}
				}
				else
				{
					Node* uncle = grandparent->_left;
					//���uncle������Ϊ�죬��parent��uncle��ڣ�grandparent���
					if (uncle && uncle->_col == RED)
					{
						parent->_col = uncle->_col = BLACK;
						grandparent->_col = RED;
						//�������ϼ��
						cur = grandparent;
						parent = cur->_parent;
					}
					//uncle�����ڻ���Ϊ��
					else
					{
						//��grandparent������grandparent��Ϊ��,parent��Ϊ��
						if (cur == parent->_right)
						{
							RotateL(grandparent);
							 grandparent->_col = RED;
							parent->_col = BLACK;
						}
						//��parent������grandparent��������cur��Ϊ�ڣ�grandparent��Ϊ��
						else
						{
							RotateR(parent);
							RotateL(grandparent);
							grandparent->_col = RED;
							cur->_col = BLACK;
						}
						break;
					}
				}
			}
			//�Ѹ��ڵ��Ϊ��
			_root->_col = BLACK;
			return make_pair(iterator(ret), true);
		}

		bool _IsRBTree(Node* root, int count, int blacknum)
		{
			if (root == nullptr)
			{
				if (count != blacknum)
				{
					return false;
				}
				return true;
			}
			if (root->_col == BLACK)
			{
				count++;
			}
			return _IsRBTree(root->_left, count, blacknum) &&
				_IsRBTree(root->_right, count, blacknum);
		}
		bool IsRBTree()
		{
			if (_root->_col == RED)
			{
				return false;
			}
			int blacknum = 0;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_col == BLACK)
				{
					blacknum++;
				}
				cur = cur->_left;
			}
			return _IsRBTree(_root, 0, blacknum);
		}
		void _InOrder(Node* root)
		{
			KeyOfT kot;
			if (root == nullptr)
			{
				return;
			}
			_InOrder(root->_left);
			cout << kot(root->_data) << " ";
			_InOrder(root->_right);
		}
		void InOrder()
		{
			_InOrder(_root);
			cout << endl;
		}
	private:
		void Destroy(Node* root)
		{
			if (root == nullptr)
			{
				return;
			}
			Destroy(root->_left);
			Destroy(root->_right);
			delete root;
		}
		//����
		void RotateL(Node* parent)
		{
			Node* subR = parent->_right;
			Node* subRL = subR->_left;
			Node* grandparent = parent->_parent;
			parent->_right = subRL;
			if (subRL)
			{
				subRL->_parent = parent;
			}
			subR->_left = parent;
			parent->_parent = subR;
			if (parent == _root)
			{
				_root = subR;
			}
			else
			{
				if (grandparent->_left == parent)
				{
					grandparent->_left = subR;
				}
				else
				{
					grandparent->_right = subR;
				}
			}
			subR->_parent = grandparent;
		}
		//�ҵ���
		void RotateR(Node* parent)
		{
			Node* subL = parent->_left;
			Node* subLR = subL->_right;
			Node* grandparent = parent->_parent;
			parent->_left = subLR;
			if (subLR)
			{
				subLR->_parent = parent;
			}
			subL->_right = parent;
			parent->_parent = subL;
			if (parent == _root)
			{
				_root = subL;
			}
			else
			{
				if (grandparent->_left == parent)
				{
					grandparent->_left = subL;
				}
				else
				{
					grandparent->_right = subL;
				}
			}
			subL->_parent = grandparent;
		}
		//����˫��
		void RotateLR(Node* parent)
		{
			Node* subL = parent->_left;
			Node* subLR = subL->_right;
			int bf = subLR->_bf;
			RotateL(subL);
			RotateR(parent);
		}
		//����˫��
		void RotateRL(Node* parent)
		{
			Node* subR = parent->_right;
			Node* subRL = parent->_left;
			int bf = subRL->_bf;
			RotateR(subR);
			RotateL(parent);
		}
		Node* _root;
	};
};
