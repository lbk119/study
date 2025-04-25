#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>
using namespace std;
namespace lbk
{
	//�����Ľṹ��
	template <class K>
	struct BSTreeNode
	{
		//���캯��
		BSTreeNode(const K& key)
			:_left(nullptr)
			,_right(nullptr)
			,_key(key)
		{}
		//��Ա����
		BSTreeNode* _left;
		BSTreeNode* _right;
		K _key;
	};

	template <class K>
	class BSTree
	{
		typedef BSTreeNode<K> Node;
	private:
		//��Ա����
		Node* _root;

	public:
		//���캯��
		BSTree()
			: _root(nullptr)
		{}

		//��������
		//��Ҫ���еݹ鹹�����������������
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

		//��ֵ���������
		//ͨ����ֵ���������ù��캯��ʵ�����󣬽�����_root�Ϳ���
		BSTree<K>& operator=(BSTree<K> t)
		{
			std::swap(_root, t._root);
			return *this;
		}

		//��������
		//��Ҫ����ɾ��
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

		//������
		//�ǵݹ�д��
		Node* Find(const K& key)
		{
			Node* cur = _root;
			while (cur)
			{
				//ֵ�Ƚ���ֵС�����ý���������
				if (key < cur->_key)
					cur = cur->_left;
				//ֵ�Ƚ���ֵ�����ý���������
				else if (key > cur->_key)
					cur = cur->_right;
				//ֵ�����ֵ��ȣ��ҵ���
				else
					return cur;
			}
			//�Ҳ���
			return nullptr;
		}
		// �ݹ�д��
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
		//������
		//�ǵݹ�д��
		bool Insert(const K& key)
		{
			Node* newnode = new Node(key);
			//��һ�β���
			if (_root == nullptr)
			{
				_root = newnode;
				return true;
			}
			//��¼���׽�㣬�������½��
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				//ֵ�Ƚ���ֵС�����ý�����������
				if (key < cur->_key)
				{
					parent = cur;
					cur = cur->_left;
				}
				//ֵ�Ƚ���ֵ�����ý�����������
				else if (key > cur->_key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					//ֵ�����ֵ��ȣ��Ѿ��и�ֵ��������
					return false;
				}
			}
			//��ʱcurΪnullptr���Բ�����
			if (key < parent->_key)
				parent->_left = newnode;
			else
				parent->_right = newnode;
			return true;
		}
		//�ݹ�д��
		bool _InsertR(Node*& cur,const K& key)
		{
			if (cur == nullptr)
			{
				//��ʱ���Բ���
				Node* newnode = new Node(key);
				//��Ϊ������cur��&����ʱ��curΪ��һ��cur�ĺ���
				//�ı�����ֱ�Ӹ�cur�������ӳɹ�
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
		//ɾ�����
		//�ǵݹ�д��
		bool Erase(const K& key)
		{
			//���������
			//1.���Ҫɾ���Ľ��û�к��ӻ���ֻ��һ������
			//��ʱֻ��Ҫ�ý��ĸ������ӽ��ĺ��Ӽ���ɾ��
			//2.���Ҫɾ���Ľ������������
			//��ʱֻ��Ҫ��һ�������㣨��ķ���������������ҽ�����������������
			//�ý���ֵ�滻Ϊ��ķ����ֵ��Ȼ��ȥɾ����ķ��㼴��(��ʱΪ���1)
			if (_root == nullptr)
			{
				return false;
			}
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				//ֵ�Ƚ���ֵС�����ý���������
				if (key < cur->_key)
				{
					parent = cur;
					cur = cur->_left;
				}
				//ֵ�Ƚ���ֵ�����ý���������
				else if (key > cur->_key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					//ֵ�����ֵ��ȣ��ҵ���,׼��ɾ��
					//���ɾ��������ֻ��һ�������ɾ������Ҫ�ı��Ϊnullptr
					if (_root->_left==nullptr&&_root->_right==nullptr)
					{
						delete _root;
						_root = nullptr;
						return true;
					}
					//���1
					if (cur->_left == nullptr || cur->_right == nullptr)
					{
						if (parent == nullptr)
						{
							//���ɾ������㣬��ɾ������Ҫ����
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
					//���2
					else
					{
						//�ұ�ķ�������������ҽ����������������㣬�����������ҽ��Ϊ��
						Node* PLeftMax = cur;
						Node* LeftMax = cur->_left;
						while (LeftMax->_right)
						{
							PLeftMax = LeftMax;
							LeftMax = LeftMax->_right;
						}
						//��ɾ������ֵ�滻Ϊ��ķ����ֵ
						cur->_key = LeftMax->_key;
						//ɾ����ķ��㣨����Ϊ�գ�
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
		//�ݹ�д��
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
				//�ҵ�ɾ��
				//���ɾ��������ֻ��һ�������ɾ������Ҫ�ı��Ϊnullptr
				if (_root->_left == nullptr && _root->_right == nullptr)
				{
					delete _root;
					_root = nullptr;
					return true;
				}
				//���1
				if (cur->_left == nullptr || cur->_right == nullptr)
				{
					Node* del = cur;
					//��Ϊ���Ĳ���Ϊ���ã����Կ���ֱ������
					cur = (cur->_left != nullptr) ? cur->_left : cur->_right;
					delete del;
				}
				//���2
				else
				{
					//�ұ�ķ�������������ҽ����������������㣬�����������ҽ��Ϊ��
					Node* LeftMax = cur->_left;
					while (LeftMax->_right)
						LeftMax = LeftMax->_right;
					//��ɾ������ֵ�뱣ķ����ֵ����
					std::swap(cur->_key , LeftMax->_key);
					//������ɾ��ԭ��ķ��㣨����Ϊ�գ�
					return _EraseR(cur->_left, key);
				}
				return true;
			}
		}
		bool EraseR(const K& key)
		{
			return _EraseR(_root, key);
		}

		//�������
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
			//������װ�����Բ��ô��ε���
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