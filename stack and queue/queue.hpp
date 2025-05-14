#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<deque>
using namespace std;
namespace lbk
{
	template<class T,class Container=deque<T>>
	class queue
	{
	public:
		template<class InputIterator>
		queue(InputIterator first, InputIterator last)
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
			_con.pop_front();
		}
		T& front()
		{
			return _con[0];
		}
		T& back()
		{
			return _con[_con.size() - 1];
		}
		size_t size()
		{
			return _con.size();
		}
		bool empty()
		{
			return _con.empty();
		}
	private:
		Container _con;
	};
}
int main()
{
	int a[] = { 1,2,3,4,5 };
	lbk::queue<int> q(a, a + sizeof(a) / sizeof(a[0]));
	while (!q.empty())
	{
		cout << q.front() << " ";
		q.pop();
	}
	return 0;
}