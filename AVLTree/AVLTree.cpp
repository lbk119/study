#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;
namespace lbk
{
	template <class K, class V>
	//���
	struct AVLTreeNode
	{
		//���캯��
		AVLTreeNode(const pair<K,V>& kv)
			:_left(nullptr)
			, _right(nullptr)
			, _parent(nullptr)
			, _bf(0)
			, _kv(kv)
		{}
		//��Ա����
		AVLTreeNode* _left;
		AVLTreeNode* _right;
		AVLTreeNode* _parent;
		int _bf;//ƽ������
		pair<K, V> _kv;//�ڵ�����
	};

	template <class K, class V>
	class AVLTree
	{
		typedef AVLTreeNode<K, V> Node;
		//��Ա����
		Node* _root;
	public:
		//���캯��
		AVLTree()
			:_root(nullptr)
		{}
		//��������
		void _Destroy(Node* root)
		{
			if (root == nullptr)
			{
				return;
			}
			_Destroy(root->_left);
			_Destroy(root->_right);
			delete root;
		}
		~AVLTree()
		{
			_Destroy(_root);
			_root = nullptr;
		}
		Node* Find(const K& key)
		{
			Node* cur = _root;
			while (cur)
			{
				if (key < cur->_kv.first)
					cur = cur->_left;
				else if (key > cur->_kv.first)
					cur = cur->_right;
				else
					return cur;
			}
			return nullptr;
		}
		//����[]
		V& operator[](const K& key)
		{
			pair<Node*, bool> ret = Insert(make_pair(key,V()));
			return ret.first->_kv.second;
		}
		//�ж��Ƿ�ΪAVLTree
		//Ҫ�����������ĸ߶Ȳ�С�ڵ���1���ҵ�����ƽ������
		int Height(Node* root)
		{
			if (root == nullptr)
			{
				return 0;
			}
			int LeftHeight = Height(root->_left);
			int RightHeight = Height(root->_right);
			return LeftHeight > RightHeight ? LeftHeight + 1 : RightHeight + 1;
		}
		bool _IsAVLTree(Node* root)
		{
			if (root == nullptr)
			{
				return true;
			}
			int LeftHeight = Height(root->_left);
			int RightHeight = Height(root->_right);
			if (RightHeight - LeftHeight!=root->_bf)
			{
				cout << root->_kv.first << "ƽ�������쳣" << endl;
				return false;
			}
			return abs(LeftHeight - RightHeight) < 2 &&
				_IsAVLTree(root->_left) && _IsAVLTree(root->_right);
		}
		bool IsAVLTree()
		{
			return _IsAVLTree(_root);
		}
		//�������
		void _InOrder(Node* root)
		{
			if (root == nullptr)
			{
				return;
			}
			_InOrder(root->_left);
			cout << root->_kv.first << " ";
			_InOrder(root->_right);
		}
		void InOrder()
		{
			_InOrder(_root);
			cout << endl;
		}
		//����
		pair<Node*, bool> Insert(const pair<K, V>& kv)
		{
			//�ڵ�һ��λ�ò���
			if (_root == nullptr)
			{
				_root = new Node(kv);
				return pair<Node*, bool>(_root, true);
			}
			Node* cur = _root, * parent = _root;
			while (cur)
			{
				if (kv.first < cur->_kv.first)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (kv.first > cur->_kv.first)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					//�Ѿ����ڲ�����
					return pair<Node*, bool>(cur, false);
				}
			}
			//�����½������
			cur = new Node(kv);
			cur->_parent = parent;
			if (kv.first < parent->_kv.first)
				parent->_left = cur;
			else
				parent->_right = cur;

			Node* ret = cur;
			//����ƽ������
			while (cur != _root)
			{
				if (cur == parent->_right)
					parent->_bf++;
				else
					parent->_bf--;
				if (parent->_bf == 0)
				{
					break;
				}
				else if (parent->_bf == 1 || parent->_bf == -1)
				{
					//�������ϸ���ƽ������
					cur = parent;
					parent = parent->_parent;
				}
				else if (parent->_bf == 2 || parent->_bf == -2)
				{
					if (parent->_bf == 2)
					{
						//����
						if (cur->_bf == 1)
							RotateL(parent);
						//����˫��
						else if (cur->_bf == -1)
							RotateRL(parent);
					}
					else if (parent->_bf == -2)
					{
						//�ҵ���
						if (cur->_bf == -1)
							RotateR(parent);
						//����˫��
						else if (cur->_bf == 1)
							RotateLR(parent);
					}
					break;
				}
			}
			return pair<Node*, bool>(ret, true);
		}
	private:
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
					grandparent->_left = subR;
				else
					grandparent->_right = subR;
			}
			subR->_parent = grandparent;
			//����ƽ������
			parent->_bf = subR->_bf = 0;
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
					grandparent->_left = subL;
				else
					grandparent->_right = subL;
			}
			subL->_parent = grandparent;
			//����ƽ������
			parent->_bf = subL->_bf = 0;
		}
		//����˫��
		void RotateLR(Node* parent)
		{
			Node* subL = parent->_left;
			Node* subLR = subL->_right;
			int bf = subLR->_bf;
			RotateL(subL);
			RotateR(parent);
			if (bf == 1)
			{
				subL->_bf = -1;
				subLR->_bf = 0;
				parent->_bf = 0;
			}
			else if (bf == -1)
			{
				subL->_bf = 0;
				subLR->_bf = 0;
				parent->_bf = 1;
			}
			else if (bf == 0)
			{
				subL->_bf = 0;
				subLR->_bf = 0;
				parent->_bf = 0;
			}
		}
		//����˫��
		void RotateRL(Node* parent)
		{
			Node* subR = parent->_right;
			Node* subRL = parent->_left;
			int bf = subRL->_bf;
			RotateR(subR);
			RotateL(parent);
			if (bf == 1)
			{
				subR->_bf = 0;
				subRL->_bf = 0;
				parent->_bf = -1;
			}
			else if (bf == -1)
			{
				subR->_bf = 1;
				subRL->_bf = 0;
				parent->_bf = 0;
			}
			else if (bf == 0)
			{
				subR->_bf = 0;
				subRL->_bf = 0;
				parent->_bf = 0;
			}
		}

	};
}
int main()
{
	vector<int> v = { 5,9,1,2,8,6,3,7,4 };
	lbk::AVLTree<int, int> a;
	for (auto e : v)
	{
		a.Insert(make_pair(e,0));
	}
	a.InOrder();
	cout << a.IsAVLTree()<<endl;
	cout << a[1];
	a[1] = 5;
	cout << a[1];

	return 0;
}
