#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>
#include <stdbool.h>
using namespace std;
namespace lbk
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		//默认成员函数
	
		//构造函数1
		vector()
			:_start(nullptr)
			,_finish(nullptr)
			,_end_of_storage(nullptr)
		{}
		//构造函数2.1
		vector(size_t n, const T& val = T())
			: _start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			resize(n, val);
		}
		//构造函数3
		template <class InputIterator>
		vector(InputIterator first, InputIterator last)
			: _start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			while (first != last)
			{
				push_back(*first);
				first++;
			}
		}
		//当有vector<int> v(10,5); 时，因为10和5都是int类型
		// 会优先调用构造函数3，所以需要重载另一个int的版本
		 //构造函数2.2
		vector(int n, const T& val = T())
			: _start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			resize(n, val);
		}
		//拷贝构造函数
		//传统写法
		//vector(const vector<T>& v)
		//	: _start(nullptr)
		//	, _finish(nullptr)
		//	, _end_of_storage(nullptr)
		//{
		//	//开辟空间
		//	reserve(v.capacity());
        //  //拷贝数据
		//	for (size_t i = 0; i < v.size(); i++)
		//	{
		//		_start[i] = v._start[i];
		//	}
		//	_finish = _start + v.size();
		//}
		//现代写法
		vector(const vector<T>& v)
			: _start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			reserve(v.capacity());
			for (auto e : v)
			{
				push_back(e);
			}
		}
		//赋值运算符重载
		//传统写法
		//vector<T>& operator=(const vector<T>& v)
		//{
		//	if (this != &v)
		//	{
		//		//开辟空间
		//		T* tmp = new T[v.capacity()];
		//		//拷贝数据
		//		for (size_t i = 0; i < v.size(); i++)
		//		{
		//			tmp[i] = v[i];
		//		}
		//		//更新
		//		delete[] _start;
		//		_start = tmp;
		//		_finish = _start + v.size();
		//		_end_of_storage = _start + v.capacity();
		//	}
		//	return *this;
		//}
		//现代写法
		vector<T>& operator=(const vector<T>& v)
		{
			if (this != &v)
			{
				vector<T> tmp(v);
				swap(tmp);
			}
			return *this;
		}
		void swap(vector<T>& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_end_of_storage, v._end_of_storage);
		}
		//析构函数
		~vector()
		{
			if (_start)
			{
				delete[] _start;
			}
			_start = _finish = _end_of_storage = nullptr;
		}

		//iterator
		iterator begin()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}
		const_iterator begin()const
		{
			return _start;
		}
		const_iterator end()const
		{
			return _finish;
		}
		//capacity
		
		size_t size()const
		{
			return _finish - _start;
		}
		size_t capacity()const
		{
			return _end_of_storage-_start;
		}
		bool empty()const
		{
			return size()==0;
		}
		void reserve(size_t n)
		{
			//开辟新空间
			T* tmp=new T[n];
			//如果容器不为空
			if (_start)
			{
				/*注意拷贝数据不能使用memcpy，因为其为浅拷贝，对于T为自定义类型
                若使用会导致新开辟的空间的元素和原空间的元素指向同一块空间，
                程序结束时会导致析构两次*/
                //memcpy(tmp, _start, size());
				size_t i = 0;
				for (; i < size(); i++)
				{
					tmp[i] = _start[i];
				}
				//更新
                //保留原来的size，不然_start更新后找不到
				size_t sz = size();
				delete[] _start;
				_start = tmp;
				_finish = _start + sz;
				_end_of_storage = _start + n;
			}
			//如果容器为空
			else
			{
				_start = _finish = tmp;
				_end_of_storage = _start + n;
			}
		}
		void resize(size_t n, const T& val = T())
		{
			//如果n<size删除数据
			if (n < size())
			{
				_finish = _start + n;
			}
			else
			{
				//判断是否需要扩容
				if (n > capacity())
				{
					reserve(n);
				}
				size_t i = size();
				for (; i < n; i++)
				{
					_start[i] = val;
				}
				_finish = _start + n;
			}
		}
		//modifiers
		
		void push_back(const T& val)
		{
			if (_finish==_end_of_storage)
			{
				size_t newcapacity = capacity() == 0 ? 4 : capacity() * 2;
				reserve(newcapacity);
			}
		    *_finish = val;
			_finish++;
		}
		void pop_back()
		{
			assert(!empty());
			_finish--;
		}
		void insert(iterator pos, const T& val)
		{
			if (_finish == _end_of_storage)
			{
				//记录原来pos相对_start的位移量，否则扩容后_start可能改变而出现错误
				size_t len = pos - _start;
				size_t newcapacity = capacity() == 0 ? 4 : capacity() * 2;
				reserve(newcapacity);
				//更新pos
				pos = _start + len;
			}
			iterator it= _finish;
			for (;it>pos; it--)
			{
				*it = *(it - 1);
			}
			*pos = val;
			_finish++;
		}
		iterator erase(iterator pos)
		{
			assert(pos >= begin());
			assert(pos < end());
			assert(!empty());
			for (iterator it = pos; it<end(); it++)
			{
				*it = *(it + 1);
			}
			--_finish;
			return pos;
		}
		//access

		T& operator[](size_t i)
		{
			assert(i < size());
			return _start[i];
		}

		const T& operator[](size_t i)const
		{
			assert(i < size());
			return _start[i];
		}
	private:
		iterator _start;
		iterator _finish;
		iterator _end_of_storage;
	};
}
int main()
{
	lbk::vector<int> v1(5, 10);
	size_t i = 0;
	for (; i < v1.size(); i++)
	{
		cout << v1[i] << ' ';
	}
	cout << endl;
	v1.push_back(6);
	v1.push_back(6);
	cout << "v1:";
	for (i=0; i < v1.size(); i++)
	{
		cout << v1[i] << ' ';
	}
	cout << endl;
	lbk::vector<int> v2;
	v2 = v1;
	cout << "v2:";
	for (i = 0; i < v2.size(); i++)
	{
		cout << v2[i] << ' ';
	}
	cout << endl;
	v2.insert(v2.begin() + 1, 7);
	for (i = 0; i < v2.size(); i++)
	{
		cout << v2[i] << ' ';
	}
	cout << endl;
	v2.erase(v2.begin() + 2);
	for (i = 0; i < v2.size(); i++)
	{
		cout << v2[i] << ' ';
	}
	cout << endl;
	return 0;
}