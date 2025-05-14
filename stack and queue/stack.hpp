#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<deque>
using namespace std;
namespace lbk
{
	template<class T,class Container=deque<T>>
	class stack
	{
	public:
		template<class InputIterator>
		stack(InputIterator first,InputIterator last)
		{
			while (first != last)
			{
				push(*first);
				first++;
			}
		}
		void push(const T& x)
		{
			_con.push_back(x);
		}
		void pop()
		{
			_con.pop_back();
		}
		T& top()
		{
			return _con[_con.size() - 1];
		}
		bool empty()
		{
			return _con.empty();
		}
		size_t size()
		{
			return _con.size();
		}
	private:
		Container _con;
	};
}
//int main()
//{
//	int a[] = { 1,2,3,4,5 };
//	lbk::stack<int> s(a, a + sizeof(a) / sizeof(a[0]));
//	while (!s.empty())
//	{
//		cout << s.top() << " ";
//		s.pop();
//	}
//	return 0;
//}