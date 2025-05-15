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
		//�����Ѿ�������\0��
		string(const char* s="")
			:_size(strlen(s))
		{
			//��֤_capacity��Ϊ0
			_capacity = _size==0 ? 3:_size;
			_str = new char[_capacity+1];
			strcpy(_str, s);
		}
		//��������
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
		//����private�ĳ�Ա
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
		//���������
		//���޸ĳ�Ա�����ĺ�����������ұ߼���const
		string& operator=(const string& s)
		{
			//��Ҫ�ж��Ƿ���ڣ���Ȼ��ֱ���ͷ�ԭ���ռ�
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
		//���������Ѿ�д���������
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
		//������
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
		//����(��������)
		void reserve(size_t newcapacity)
		{
			assert(newcapacity >= _capacity);
			_capacity = newcapacity;
			char* tmp = new char[_capacity + 1];
			strcpy(tmp, _str);
			delete[] _str;
			_str = tmp;
		}
		//resize���ı�ԭ��string��ֵ
		void resize(size_t newsize,char ch='\0')
		{
			//��newsize<_sizeʱ����Ҫɾ������
			if (newsize < _size)
			{
				_size = newsize;
				_str[_size] = '\0';
			}
			else
			{
				//����
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
				//Ϊ�˷�ֹƵ�����ݣ�����һ��������Щ
				reserve(_capacity * 2);
			}
			_str[_size] = ch;
			_size++;
			_str[_size] = '\0';//��'\0'����ȥ
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
			//Ų������
			_size++;
			size_t i = _size;
			while (i > pos)
			{
				_str[i] = _str[i - 1];
				i--;
			}
			//��������
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
			//Ų������
			size_t i = _size;
			while (i > pos)
			{
				_str[i + len] = _str[i];
				i--;
			}
			_size += len;
			//��������
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
		//��̬��Ա�������������ж��壬��Ҫ�����ⶨ��
		static size_t npos;
	};
	size_t string::npos = -1;
	//����ȡ�������붼��Ҫ������ʵ�֣���ֹthisռ��һ������
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
		//���ԭ��s�е�ֵ
		s.clear();
		/*char ch;
		in >> ch;*/
		//���ϴ��벻��ʵ�֣���Ϊch������ڿո���з���
		//��in�лὫ�ո���з�������ͬԪ�ؼ�Ŀո񣬲��ḳ��ch
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
	//��������ʹ��
	lbk::string::iterator it = s1.begin();
	while (it != s1.end())
	{
		cout << *it;
		it++;
	}
	cout << endl;
	//forѭ����ʹ��
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