#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>
using namespace std;
namespace lbk
{
	//结点类
	template <class T>
	struct _list_node
	{
		//构造函数
		_list_node(const T& val=T())
			:val(val)
			,next(nullptr)
			,prev(nullptr)
		{}

		//成员变量
		T val;
		struct _list_node<T>* next;
		struct _list_node<T>* prev;
	};
	//迭代器
	//Ref为T&和const T&类型，Ptr为T*和const T*类型
	template<class T,class Ref,class Ptr>
	struct _list_iterator
	{
		typedef _list_node<T> node;
		typedef _list_iterator<T,Ref,Ptr> iterator;
		//构造函数
		_list_iterator(node* pnode)
			:_pnode(pnode)
		{}
		//运算符重载
		//前置++
		iterator& operator++()
		{
			_pnode = _pnode->next;
			return *this;
		}
		//后置++
		iterator operator++(int)
		{
			iterator tmp(_pnode);
			_pnode = _pnode->next;
			return tmp;
		}
		//前置--
		iterator& operator--()
		{
			_pnode = _pnode->prev;
			return *this;
		}
		//后置--
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
		//Ref为T&和const T&类型
		Ref operator*()
		{
			return _pnode->val;
		}
		//当list中val为自定义类型时，可以通过->来访问自定义类对象
		//Ptr为T*和const T*类型
		Ptr operator->()
		{
			return &(_pnode->val);
		}
		//成员变量
		node* _pnode;
	};
	//反向迭代器
	template<class T, class Ref, class Ptr>
	struct _reverse_list_iterator
	{
		typedef _list_node<T> node;
		typedef _list_iterator<T, Ref, Ptr> iterator;
		typedef _reverse_list_iterator<T, Ref, Ptr> reverse_iterator;
		//构造函数
		_reverse_list_iterator(iterator it)
			:_it(it)
		{}
		//运算符重载
		//前置++
		reverse_iterator& operator++()
		{
			--_it;
			return *this;
		}
		//后置++
		reverse_iterator operator++(int)
		{
			reverse_iterator tmp(_it);
			--_it;
			return tmp;
		}
		//前置--
		reverse_iterator& operator--()
		{
			++_it;
			return *this;
		}
		//后置--
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
		//Ref为T&和const T&类型
		Ref operator*()
		{
			iterator prev = _it;
			return *(--prev);
		}
		//当list中val为自定义类型时，可以通过->来访问自定义类对象
        //Ptr为T*和const T*类型
		Ptr operator->()
		{
			iterator prev = _it;
			prev--;
			return &(prev->val);
		}
		//成员变量
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
		//默认成员函数
		
		//构造函数
		list()
		{
			_head = new node;
			_head->next = _head;
			_head->prev = _head;
		}
		//拷贝构造
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
		//重载赋值运算符
		list<T>& operator=(const list<T>& lt)
		{
			if (this != &lt)//防止给自己赋值
			{
				clear();
				for (auto& e : lt)
				{
					push_back(e);
				}
			}
			return *this;
		}
		//析构函数
		~list()
		{
			clear();//释放头结点以外的结点
			delete _head;//释放头结点
			_head = nullptr;
		}
		//迭代器相关函数
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
		//访问容器相关函数
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
			assert(pos._pnode);//保证指针不为空
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
			assert(pos._pnode != _head);//不能删头结点
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
			erase(--end());//end()返回头结点的迭代器，不能删头结点
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
		void clear()//只保留头结点
		{
			iterator it = begin();
			while (it != end())
			{
				it=erase(it);//因为it在用erase后失效，需要重新赋值
			}
		}
		void swap(list<T>& lt)
		{
			std::swap(_head, lt._head);
		}
		void resize(size_t n,const T& val=T())
		{
			//如果n<size()，则删除
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
		//成员变量
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