#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>
using namespace std;
namespace lbk
{
	//�����
	template <class T>
	struct _list_node
	{
		//���캯��
		_list_node(const T& val=T())
			:val(val)
			,next(nullptr)
			,prev(nullptr)
		{}

		//��Ա����
		T val;
		struct _list_node<T>* next;
		struct _list_node<T>* prev;
	};
	//������
	//RefΪT&��const T&���ͣ�PtrΪT*��const T*����
	template<class T,class Ref,class Ptr>
	struct _list_iterator
	{
		typedef _list_node<T> node;
		typedef _list_iterator<T,Ref,Ptr> iterator;
		//���캯��
		_list_iterator(node* pnode)
			:_pnode(pnode)
		{}
		//���������
		//ǰ��++
		iterator& operator++()
		{
			_pnode = _pnode->next;
			return *this;
		}
		//����++
		iterator operator++(int)
		{
			iterator tmp(_pnode);
			_pnode = _pnode->next;
			return tmp;
		}
		//ǰ��--
		iterator& operator--()
		{
			_pnode = _pnode->prev;
			return *this;
		}
		//����--
		iterator operator--(int)
		{
			iterator tmp(_pnode);
			_pnode = _pnode->prev;
			return tmp;
		}
		bool operator==(const iterator& x)
		{
			return _pnode == x._pnode;
		}
		bool operator!=(const iterator& x)
		{
			return _pnode != x._pnode;
		}
		//RefΪT&��const T&����
		Ref operator*()
		{
			return _pnode->val;
		}
		//��list��valΪ�Զ�������ʱ������ͨ��->�������Զ��������
		//PtrΪT*��const T*����
		Ptr operator->()
		{
			return &(_pnode->val);
		}
		//��Ա����
		node* _pnode;
	};
	//���������
	template<class T, class Ref, class Ptr>
	struct _reverse_list_iterator
	{
		typedef _list_node<T> node;
		typedef _list_iterator<T, Ref, Ptr> iterator;
		typedef _reverse_list_iterator<T, Ref, Ptr> reverse_iterator;
		//���캯��
		_reverse_list_iterator(iterator it)
			:_it(it)
		{}
		//���������
		//ǰ��++
		reverse_iterator& operator++()
		{
			--_it;
			return *this;
		}
		//����++
		reverse_iterator operator++(int)
		{
			reverse_iterator tmp(_it);
			--_it;
			return tmp;
		}
		//ǰ��--
		reverse_iterator& operator--()
		{
			++_it;
			return *this;
		}
		//����--
		reverse_iterator operator--(int)
		{
			reverse_iterator tmp(_it);
			++_it;
			return tmp;
		}
		bool operator==(const reverse_iterator& x)
		{
			return _it==x._it;
		}
		bool operator!=(const reverse_iterator& x)
		{
			return _it != x._it;
		}
		//RefΪT&��const T&����
		Ref operator*()
		{
			iterator prev = _it;
			return *(--prev);
		}
		//��list��valΪ�Զ�������ʱ������ͨ��->�������Զ��������
        //PtrΪT*��const T*����
		Ptr operator->()
		{
			iterator prev = _it;
			prev--;
			return &(prev->val);
		}
		//��Ա����
		iterator _it;
	};
	template <class T>
	class list
	{
	public:
		typedef _list_node<T> node;
		typedef _list_iterator<T, T&, T*> iterator;
		typedef _reverse_list_iterator<T, T&, T*> reverse_iterator;
		typedef _list_iterator<T, const T&, const T*> const_iterator;
		typedef _reverse_list_iterator<T, const T&, const T*> const_reverse_iterator;
		//Ĭ�ϳ�Ա����
		
		//���캯��
		list()
		{
			_head = new node;
			_head->next = _head;
			_head->prev = _head;
		}
		//��������
		list(const list<T>& lt)
		{
			_head = new node;
			_head->next = _head;
			_head->prev = _head;
			for (auto& e : lt)
			{
				push_back(e);
			}
		}
		//���ظ�ֵ�����
		list<T>& operator=(const list<T>& lt)
		{
			if (this != &lt)//��ֹ���Լ���ֵ
			{
				clear();
				for (auto& e : lt)
				{
					push_back(e);
				}
			}
			return *this;
		}
		//��������
		~list()
		{
			clear();//�ͷ�ͷ�������Ľ��
			delete _head;//�ͷ�ͷ���
			_head = nullptr;
		}
		//��������غ���
		iterator begin()
		{
			return iterator(_head->next);
		}
		iterator end()
		{
			return iterator(_head);
		}
		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}
		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}
		const_iterator begin()const
		{
			return const_iterator(_head->next);
		}
		const_iterator end()const
		{
			return const_iterator(_head);
		}
		const_reverse_iterator rbegin()const
		{
			return const_reverse_iterator(end());
		}
		const_reverse_iterator rend()const
		{
			return const_reverse_iterator(begin());
		}
		//����������غ���
		T& front()
		{
			return *begin();
		}
		T& back()
		{
			return *(--end());
		}
		const T& front()const
		{
			return *begin();
		}
		const T& back()const
		{
			return *(--end());
		}
		//modifiers
		void insert(iterator pos, const T& val)
		{
			assert(pos._pnode);//��ָ֤�벻Ϊ��
			node* newnode = new node(val);
			node* curnode = pos._pnode;
			node* prevnode = pos._pnode->prev;
			curnode->prev = newnode;
			newnode->prev = prevnode;
			newnode->next = curnode;
			prevnode->next = newnode;
		}
		iterator erase(iterator pos)
		{
			assert(!empty());
			assert(pos._pnode != _head);//����ɾͷ���
			node* prevnode = pos._pnode->prev;
			node* nextnode = pos._pnode->next;
			delete pos._pnode;
			prevnode->next = nextnode;
			nextnode->prev = prevnode;
			return iterator(nextnode);
		}
		void push_front(const T& val)
		{
			insert(begin(), val);
		}
		void push_back(const T& val)
		{
			insert(end(), val);
		}
		void pop_front()
		{
			erase(begin());
		}
		void pop_back()
		{
			erase(--end());//end()����ͷ���ĵ�����������ɾͷ���
		}
		//other
		bool empty()const
		{
			return begin() == end();
		}
		size_t size()const
		{
			size_t sz = 0;
			const_iterator it = begin();
			while (it != end())
			{
				it++;
				sz++;
			}
			return sz;
		}
		void clear()//ֻ����ͷ���
		{
			iterator it = begin();
			while (it != end())
			{
				it=erase(it);//��Ϊit����erase��ʧЧ����Ҫ���¸�ֵ
			}
		}
		void swap(list<T>& lt)
		{
			std::swap(_head, lt._head);
		}
		void resize(size_t n,const T& val=T())
		{
			//���n<size()����ɾ��
			if (n < size())
			{
				size_t count = size() - n;
				while (count > 0)
				{
					pop_back();
					count--;
				}
			}
			else
			{
				size_t count = n-size();
				while (count > 0)
				{
					push_back(val);
					count--;
				}
			}
		}
	private:
		//��Ա����
		node* _head;
	};
}
int main()
{
	lbk::list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_front(0);
	lt.erase(lt.begin());
	lbk::list<int>::reverse_iterator it = lt.rbegin();
	while (it != lt.rend())
	{
		cout << *it << ' ';
		it++;
	}
	cout << endl;
	return 0;
}