#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>
#include<string>
using namespace std;
namespace lbk
{
	class string
	{
	public:
		//“”已经包括‘\0’
		string(const char* s="")
			:_size(strlen(s))
		{
			//保证_capacity不为0
			_capacity = _size==0 ? 3:_size;
			_str = new char[_capacity+1];
			strcpy(_str, s);
		}
		//拷贝构造
		string(const string& s)
			:_size(s._size)
			,_capacity(s._capacity)
		{
			_str = new char[_capacity + 1];
			strcpy(_str, s._str);
		}
		~string()
		{
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}
		//访问private的成员
		const char* c_str() const
		{
			return _str;
		}
		size_t size()const
		{
			return _size;
		}
		size_t capacity()const
		{
			return _capacity;
		}
		//运算符重载
		//不修改成员变量的函数，最好在右边加上const
		string& operator=(const string& s)
		{
			//需要判断是否等于，不然会直接释放原来空间
			if (this != &s)
			{
				delete[] _str;
				_size = s._size;
				_capacity = s._capacity;
				_str = new char[_capacity + 1];
				strcpy(_str, s._str);
			}
			return *this;
		}
		char& operator[](size_t pos)
		{
			assert(pos < _size);
			return _str[pos];
		}
		const char& operator[](size_t pos) const
		{
			assert(pos < _size);
			return _str[pos];
		}
		bool operator>(const string& s) const
		{
			return strcmp(_str, s._str)>0;
		}
		bool operator==(const string& s)const
		{
			return strcmp(_str, s._str) == 0;
		}
		//复用上述已经写过的运算符
		bool operator!=(const string& s)const
		{
			return !(*this == s);
		}
		bool operator>=(const string& s)const
		{
			return (*this> s) || (*this == s);
		}
		bool operator<(const string& s)const
		{
			return !(*this >= s);
		}
		bool operator<=(const string& s)const
		{
			return (*this < s) || (*this == s);
		}
		//迭代器
		typedef char* iterator;
		typedef const char* const_iterator;
		iterator begin()const
		{
			return _str;
		}
		iterator end()const
		{
			return _str + _size;
		}
		const_iterator cbegin()const
		{
			return _str;
		}
		const_iterator cend()const
		{
			return _str + _size;
		}
		//扩容(不能缩容)
		void reserve(size_t newcapacity)
		{
			assert(newcapacity >= _capacity);
			_capacity = newcapacity;
			char* tmp = new char[_capacity + 1];
			strcpy(tmp, _str);
			delete[] _str;
			_str = tmp;
		}
		//resize不改变原先string的值
		void resize(size_t newsize,char ch='\0')
		{
			//当newsize<_size时，需要删除数据
			if (newsize < _size)
			{
				_size = newsize;
				_str[_size] = '\0';
			}
			else
			{
				//扩容
				if (newsize > _capacity)
				{
					reserve(newsize);
				}
				while (_size < newsize)
				{
					_str[_size] = ch;
					_size++;
				}
				_str[_size] = '\0';
			}
		}
		void push_back(char ch)
		{
			if (_size + 1 > _capacity)
			{
				//为了防止频繁扩容，可以一次性扩大些
				reserve(_capacity * 2);
			}
			_str[_size] = ch;
			_size++;
			_str[_size] = '\0';//将'\0'补上去
		}
		void append(char* s)
		{
			size_t len = strlen(s);
			if (_size + len > _capacity)
			{
				size_t newcapacity = (_size + len > _capacity * 2)?
					_size + len : _capacity * 2;
				reserve(newcapacity);
			}
			strcpy(_str + _size, s);
			_size += len;
		}
		void insert(size_t pos, char ch)
		{
			assert(pos <= _size);
			if (_size + 1 > _capacity)
			{
				reserve(_capacity * 2);
			}
			//挪动数据
			_size++;
			size_t i = _size;
			while (i > pos)
			{
				_str[i] = _str[i - 1];
				i--;
			}
			//插入数据
			_str[i] = ch;
		}
		void insert(size_t pos, const char* s)
		{
			assert(pos <= _size);
			size_t len = strlen(s);
			if (_size + len> _capacity)
			{
				size_t newcapacity = (_size + len > _capacity * 2) ?
					_size + len : _capacity * 2;
				reserve(newcapacity);
			}
			//挪动数据
			size_t i = _size;
			while (i > pos)
			{
				_str[i + len] = _str[i];
				i--;
			}
			_size += len;
			//插入数据
			strncpy(_str + pos, s, len);
		}
		void erase(size_t pos,size_t len=npos)
		{
			assert(pos < _size);
			if (len == npos||len+pos>_size)
			{
				_str[pos] = '\0';
				_size = pos;
			}
			else
			{
				strcpy(_str + pos, _str + pos + len);
				_size -= len;
			}
		}
		string& operator+=(char ch)
		{
			push_back(ch);
			return *this;
		}
		string& operator+=(char* s)
		{
			append(s);
			return *this;
		}
		void swap(string& s)
		{
			std::swap(_str, s._str);
			std::swap(_capacity, s._capacity);
			std::swap(_size, s._size);
		}
		size_t find(char ch,size_t pos=0)
		{
			assert(pos < _size);
			size_t i = pos;
			for (; i <= _size; i++)
			{
				if (_str[i] == ch)
				{
					return i;
				}
			}
			return npos;
		}
		size_t find(const char* s, size_t pos = 0)
		{
			assert(pos < _size);
			char* p=strstr(_str, s);
			if (p == nullptr)
			{
				return npos;
			}
			return p - _str;
		}
		void clear()
		{
			_str[0] = '\0';
			_size = 0;
		}
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
		//静态成员变量不能在类中定义，需要在类外定义
		static size_t npos;
	};
	size_t string::npos = -1;
	//流提取和流插入都需要在类外实现，防止this占第一个参数
	ostream& operator<<(ostream& out,string& s)
	{
		for (auto e : s)
		{
			out << e;
		}
		return out;
	}
	istream& operator>>(istream& in, string& s)
	{
		//清除原先s中的值
		s.clear();
		/*char ch;
		in >> ch;*/
		//以上代码不能实现，因为ch不会等于空格或换行符，
		//在in中会将空格或换行符看作不同元素间的空格，不会赋给ch
		char ch = in.get();
		char buff[128];
		int i = 0;
		while (ch != ' ' && ch != '\n')
		{
			if (i == 127)
			{
				buff[127] = '\0';
				s += buff;
				i = 0;
			}
			buff[i] = ch;
			i++;
			ch = in.get();
			//in >> ch;
		}
		if (i != 0)
		{
			buff[i] = '\0';
			s += buff;
		}
		return in;
	}
}
int main()
{
	lbk::string s1("hello world");
	string s2("hello world");
	cout << s1<<endl;
	//迭代器的使用
	lbk::string::iterator it = s1.begin();
	while (it != s1.end())
	{
		cout << *it;
		it++;
	}
	cout << endl;
	//for循坏的使用
	for (auto ch : s1)
	{
		cout << ch;
	}
	s1.insert(5, 'h');
	s2.insert(5, 1,'h');
	s1.insert(5, "xxxx");
	s2.insert(5, "xxxx");
	cout << s1.c_str() << endl;
	cout << s1 << endl;
	return 0;
}