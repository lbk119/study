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
		//Ĭ�ϳ�Ա����
	
		//���캯��1
		vector()
			:_start(nullptr)
			,_finish(nullptr)
			,_end_of_storage(nullptr)
		{}
		//���캯��2.1
		vector(size_t n, const T& val = T())
			: _start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			resize(n, val);
		}
		//���캯��3
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
		//����vector<int> v(10,5); ʱ����Ϊ10��5����int����
		// �����ȵ��ù��캯��3��������Ҫ������һ��int�İ汾
		 //���캯��2.2
		vector(int n, const T& val = T())
			: _start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			resize(n, val);
		}
		//�������캯��
		//��ͳд��
		//vector(const vector<T>& v)
		//	: _start(nullptr)
		//	, _finish(nullptr)
		//	, _end_of_storage(nullptr)
		//{
		//	//���ٿռ�
		//	reserve(v.capacity());
        //  //��������
		//	for (size_t i = 0; i < v.size(); i++)
		//	{
		//		_start[i] = v._start[i];
		//	}
		//	_finish = _start + v.size();
		//}
		//�ִ�д��
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
		//��ֵ���������
		//��ͳд��
		//vector<T>& operator=(const vector<T>& v)
		//{
		//	if (this != &v)
		//	{
		//		//���ٿռ�
		//		T* tmp = new T[v.capacity()];
		//		//��������
		//		for (size_t i = 0; i < v.size(); i++)
		//		{
		//			tmp[i] = v[i];
		//		}
		//		//����
		//		delete[] _start;
		//		_start = tmp;
		//		_finish = _start + v.size();
		//		_end_of_storage = _start + v.capacity();
		//	}
		//	return *this;
		//}
		//�ִ�д��
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
		//��������
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
			//�����¿ռ�
			T* tmp=new T[n];
			//���������Ϊ��
			if (_start)
			{
				/*ע�⿽�����ݲ���ʹ��memcpy����Ϊ��Ϊǳ����������TΪ�Զ�������
                ��ʹ�ûᵼ���¿��ٵĿռ��Ԫ�غ�ԭ�ռ��Ԫ��ָ��ͬһ��ռ䣬
                �������ʱ�ᵼ����������*/
                //memcpy(tmp, _start, size());
				size_t i = 0;
				for (; i < size(); i++)
				{
					tmp[i] = _start[i];
				}
				//����
                //����ԭ����size����Ȼ_start���º��Ҳ���
				size_t sz = size();
				delete[] _start;
				_start = tmp;
				_finish = _start + sz;
				_end_of_storage = _start + n;
			}
			//�������Ϊ��
			else
			{
				_start = _finish = tmp;
				_end_of_storage = _start + n;
			}
		}
		void resize(size_t n, const T& val = T())
		{
			//���n<sizeɾ������
			if (n < size())
			{
				_finish = _start + n;
			}
			else
			{
				//�ж��Ƿ���Ҫ����
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
				//��¼ԭ��pos���_start��λ�������������ݺ�_start���ܸı�����ִ���
				size_t len = pos - _start;
				size_t newcapacity = capacity() == 0 ? 4 : capacity() * 2;
				reserve(newcapacity);
				//����pos
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