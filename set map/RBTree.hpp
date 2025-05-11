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
	//当我们需要存储键值对，那么T就是pair<K, V>
	//当我们只存储key值，那么T就是K
	template <class T>
	struct RBTreeNode
	{
		//构造函数
		RBTreeNode(T data)
			:_left(nullptr)
			, _right(nullptr)
			, _parent(nullptr)
			, _data(data)
			, _col(RED)
		{}
		//成员变量
		RBTreeNode* _left;
		RBTreeNode* _right;
		RBTreeNode* _parent;
		T _data;//节点数据
		Color _col;//颜色
	};
	//实现迭代器
	template<class T, class Ref, class Ptr>
	struct RBTreeIterator
	{
		typedef RBTreeNode<T> Node;
		typedef RBTreeIterator<T, Ref, Ptr> Self;
		Node* _node;
		//构造函数
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
		//前置++
		Self& operator++()
		{
			//如果右子树不为空，说明该树未取完，要取右子树的最左结点
			if (_node->_right)
			{
				Node* left = _node->_right;
				while (left->_left)
				{
					left = left->_left;
				}
				_node = left;
			}
			//右子树为空，说明该树已经取完，要回到cur为左孩子的parent
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
		//后置++
		Self operator++(int)
		{
			Self old = new Self(_node);
			//如果右子树不为空，说明该树未取完，要取右子树的最左结点
			if (_node->_right)
			{
				Node* left = _node->_right;
				while (left->_left)
				{
					left = left->_left;
				}
				_node = left;
			}
			//右子树为空，说明该树已经取完，要回到cur为左孩子的parent
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
		//前置--
		Self& operator--()
		{
			Self old = new Self(_node);
			//如果左子树不为空，说明该树未取完，要取左子树的最右结点
			if (_node->_left)
			{
				Node* right = _node->_left;
				while (right->_right)
				{
					right = right->_right;
				}
				_node = right;
			}
			//左子树为空，说明该树已经取完，要回到cur为右孩子的parent
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
		//后置--
		Self operator--(int)
		{
			//如果左子树不为空，说明该树未取完，要取左子树的最右结点
			if (_node->_left)
			{
				Node* right = _node->_left;
				while (right->_right)
				{
					right = right->_right;
				}
				_node = right;
			}
			//左子树为空，说明该树已经取完，要回到cur为右孩子的parent
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
	//前面的K用于传入key的类型，后面的T用于传入红黑树存储的数据类型。
	////keyOfT仿函数，取出T对象中的key,用于比较
	template<class K, class T, class KeyOfT>
	class RBTree
	{
		typedef typename RBTreeNode<T> Node;
		typedef typename RBTreeIterator<T, T&, T*> iterator;
	public:
		//构造函数
		RBTree()
			:_root(nullptr)
		{} 
		//析构函数
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
			//找位置插入
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
			//检查颜色(当连续出现两个红色时需要调整)
			while (parent && parent->_col == RED)
			{
				Node* grandparent = parent->_parent;
				if (parent == grandparent->_left)
				{
					Node* uncle = grandparent->_right;
					//如果uncle存在且为红，则将parent和uncle变黑，grandparent变红
					if (uncle && uncle->_col == RED)
					{
						parent->_col = uncle->_col = BLACK;
						grandparent->_col = RED;
						//继续向上检查
						cur = grandparent;
						parent = cur->_parent;
					}
					//uncle不存在或者为黑
					else
					{
						//将grandparent右旋，grandparent变为红,parent变为黑
						if (cur == parent->_left)
						{
							RotateR(grandparent);
							grandparent->_col = RED;
							parent->_col = BLACK;
						}
						//将parent左旋，grandparent右旋，将cur变为黑，grandparent变为红
						else
						{
							RotateL(parent);
							RotateR(grandparent);
							grandparent->_col =  RED;
							cur->_col = BLACK;
						}
						//此时最上面的结点为黑，可以直接结束
						break;
					}
				}
				else
				{
					Node* uncle = grandparent->_left;
					//如果uncle存在且为红，则将parent和uncle变黑，grandparent变红
					if (uncle && uncle->_col == RED)
					{
						parent->_col = uncle->_col = BLACK;
						grandparent->_col = RED;
						//继续向上检查
						cur = grandparent;
						parent = cur->_parent;
					}
					//uncle不存在或者为黑
					else
					{
						//将grandparent左旋，grandparent变为红,parent变为黑
						if (cur == parent->_right)
						{
							RotateL(grandparent);
							 grandparent->_col = RED;
							parent->_col = BLACK;
						}
						//将parent右旋，grandparent左旋，将cur变为黑，grandparent变为红
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
			//把根节点变为黑
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
		//左单旋
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
		//右单旋
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
		//左右双旋
		void RotateLR(Node* parent)
		{
			Node* subL = parent->_left;
			Node* subLR = subL->_right;
			int bf = subLR->_bf;
			RotateL(subL);
			RotateR(parent);
		}
		//右左双旋
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
