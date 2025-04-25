#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>
using namespace std;
namespace lbk
{
	//树结点的结构体
	template <class K>
	struct BSTreeNode
	{
		//构造函数
		BSTreeNode(const K& key)
			:_left(nullptr)
			,_right(nullptr)
			,_key(key)
		{}
		//成员变量
		BSTreeNode* _left;
		BSTreeNode* _right;
		K _key;
	};

	template <class K>
	class BSTree
	{
		typedef BSTreeNode<K> Node;
	private:
		//成员变量
		Node* _root;

	public:
		//构造函数
		BSTree()
			: _root(nullptr)
		{}

		//拷贝构造
		//需要进行递归构造出左子树和右子树
		Node* Copy(Node* cur)
		{
			if (cur == nullptr)
			{
				return nullptr;
			}
			Node* copy = new Node(cur->_key);
			copy->_left = Copy(cur->_left);
			copy->_right = Copy(cur->_right);
			return cur;
		}
		BSTree(const BSTree<K>& t)
		{
			_root=Copy(t._root);
		}

		//赋值运算符重载
		//通过传值，参数调用构造函数实例化后，交换两_root就可以
		BSTree<K>& operator=(BSTree<K> t)
		{
			std::swap(_root, t._root);
			return *this;
		}

		//析构函数
		//需要遍历删除
		void Destroy(Node* cur)
		{
			if (cur == nullptr)
			{
				return;
			}
			Destroy(cur->_left);
			Destroy(cur->_right);
			delete cur;
		}
		~BSTree()
		{
			Destroy(_root);
			_root = nullptr;
		}

		//查早结点
		//非递归写法
		Node* Find(const K& key)
		{
			Node* cur = _root;
			while (cur)
			{
				//值比结点的值小，往该结点的左树找
				if (key < cur->_key)
					cur = cur->_left;
				//值比结点的值大，往该结点的右树找
				else if (key > cur->_key)
					cur = cur->_right;
				//值与结点的值相等，找到了
				else
					return cur;
			}
			//找不到
			return nullptr;
		}
		// 递归写法
		Node* _FindR(Node* cur,const K& key)
		{
			if (cur == nullptr)
				return nullptr;
			if (key < cur->_key)
				FindR(cur->_left, key);
			else if (key > cur->_key)
				FindR(cur->_right, key);
			else
				return cur;
		}
		Node* FindR(const K& key)
		{
			return _FindR(_root, key);
		}
		//插入结点
		//非递归写法
		bool Insert(const K& key)
		{
			Node* newnode = new Node(key);
			//第一次插入
			if (_root == nullptr)
			{
				_root = newnode;
				return true;
			}
			//记录父亲结点，来链接新结点
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				//值比结点的值小，往该结点的左树插入
				if (key < cur->_key)
				{
					parent = cur;
					cur = cur->_left;
				}
				//值比结点的值大，往该结点的右树插入
				else if (key > cur->_key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					//值与结点的值相等，已经有该值，不插入
					return false;
				}
			}
			//此时cur为nullptr可以插入结点
			if (key < parent->_key)
				parent->_left = newnode;
			else
				parent->_right = newnode;
			return true;
		}
		//递归写法
		bool _InsertR(Node*& cur,const K& key)
		{
			if (cur == nullptr)
			{
				//此时可以插入
				Node* newnode = new Node(key);
				//因为传的是cur的&，此时的cur为上一个cur的孩子
				//的别名，直接改cur即可链接成功
				cur = newnode;
				return true;
			}
			if (key < cur->_key)
				_InsertR(cur->_left,key);
			else if (key > cur->_key)
				_InsertR(cur->_right, key);
			else
				return false;
		}
		bool InsertR(const K& key)
		{
			return _InsertR(_root, key);
		}
		//删除结点
		//非递归写法
		bool Erase(const K& key)
		{
			//分两种情况
			//1.如果要删除的结点没有孩子或者只有一个孩子
			//此时只需要让结点的父亲链接结点的孩子即可删除
			//2.如果要删除的结点有两个孩子
			//此时只需要找一个代替结点（保姆），即左树的最右结点或者右树的最左结点
			//让结点的值替换为保姆结点的值，然后去删除保姆结点即可(此时为情况1)
			if (_root == nullptr)
			{
				return false;
			}
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				//值比结点的值小，往该结点的左树找
				if (key < cur->_key)
				{
					parent = cur;
					cur = cur->_left;
				}
				//值比结点的值大，往该结点的右树找
				else if (key > cur->_key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					//值与结点的值相等，找到了,准备删除
					//如果删除根，且只有一个结点则删除后需要改变根为nullptr
					if (_root->_left==nullptr&&_root->_right==nullptr)
					{
						delete _root;
						_root = nullptr;
						return true;
					}
					//情况1
					if (cur->_left == nullptr || cur->_right == nullptr)
					{
						if (parent == nullptr)
						{
							//如果删除根结点，则删除后需要更新
							_root = (cur->_left != nullptr) ? cur->_left : cur->_right;
						}
						else
						{
							if (cur->_key < parent->_key)
								parent->_left = (cur->_left != nullptr) ? cur->_left : cur->_right;
							else
								parent->_right = (cur->_left != nullptr) ? cur->_left : cur->_right;
						}
						delete cur;
					}
					//情况2
					else
					{
						//找保姆，即左树的最右结点或者右树的最左结点，以左树的最右结点为例
						Node* PLeftMax = cur;
						Node* LeftMax = cur->_left;
						while (LeftMax->_right)
						{
							PLeftMax = LeftMax;
							LeftMax = LeftMax->_right;
						}
						//将删除结点的值替换为保姆结点的值
						cur->_key = LeftMax->_key;
						//删除保姆结点（右树为空）
						if (LeftMax->_key < PLeftMax->_key)
							PLeftMax->_left = LeftMax->_left;
						else
							PLeftMax->_right = LeftMax->_left;
						delete LeftMax;
					}
					return true;
				}
			}
			return false;
		}
		//递归写法
		bool _EraseR(Node*& cur, const K& key)
		{
			if (cur == nullptr)
				return false;
			else if (key < cur->_key)
				return _EraseR(cur->_left,key);
			else if (key > cur->_key)
				return _EraseR(cur->_right, key);
			else
			{
				//找到删除
				//如果删除根，且只有一个结点则删除后需要改变根为nullptr
				if (_root->_left == nullptr && _root->_right == nullptr)
				{
					delete _root;
					_root = nullptr;
					return true;
				}
				//情况1
				if (cur->_left == nullptr || cur->_right == nullptr)
				{
					Node* del = cur;
					//因为传的参数为引用，所以可以直接连接
					cur = (cur->_left != nullptr) ? cur->_left : cur->_right;
					delete del;
				}
				//情况2
				else
				{
					//找保姆，即左树的最右结点或者右树的最左结点，以左树的最右结点为例
					Node* LeftMax = cur->_left;
					while (LeftMax->_right)
						LeftMax = LeftMax->_right;
					//将删除结点的值与保姆结点的值交换
					std::swap(cur->_key , LeftMax->_key);
					//往左树删除原保姆结点（右树为空）
					return _EraseR(cur->_left, key);
				}
				return true;
			}
		}
		bool EraseR(const K& key)
		{
			return _EraseR(_root, key);
		}

		//中序遍历
		void _InOrder(Node* cur)
		{
			if (cur == nullptr)
				return;
			_InOrder(cur->_left);
			cout << cur->_key << " ";
			_InOrder(cur->_right);
		}
		void InOrder()
		{
			//函数包装，可以不用传参调用
			_InOrder(_root);
			cout << endl;
		}


	};
}
int main()
{
	lbk::BSTree<int> t;
	t.Insert(5);
	t.Insert(4);
	t.Insert(2);
	t.Insert(1);
	t.Insert(3);
	t.InOrder();
	t.Erase(5);
	t.EraseR(1);
	t.InOrder();

	return 0;
}