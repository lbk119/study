#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;
namespace lbk
{
	//仿函数
	template <class T>
	struct less
	{
		bool operator()(const T& x, const T& y)const
		{
			return x < y;
		}
	};
	template <class T>
	struct greater
	{
		bool operator()(const T& x, const T& y)const
		{
			return x > y;
		}
	};
	//模拟实现priority_queue
	template<class T,class Container=std::vector<T>,class Compare=less<T>>
	class priority_queue
	{
	public:
		priority_queue() = default;
		template<class InputIterator>
		priority_queue(InputIterator first,InputIterator last)
		{
			while (first != last)
			{
				_con.push_back(*first);
				first++;
			}
			for (int i = (_con.size() - 1 - 1) / 2; i >= 0; i--)
			{
				adjust_down(i);
			}
		}
		void adjust_up(int child)
		{
			int parent = (child-1) / 2;
			while (child>0)
			{
				if (_com(_con[parent],_con[child]))
				{
					std::swap(_con[child],_con[parent]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
				{
					break;
				}
			}
		}
		void push(const T& val)
		{
			//在尾插入
			_con.push_back(val);
			//向上调整
			adjust_up(_con.size()-1);
		}
		void adjust_down(int parent)
		{
			int child = parent * 2 + 1;
			while (child < _con.size())
			{
				if (child + 1 < _con.size() && _com(_con[child], _con[child + 1]))
				{
					child++;
				}
				if (_com(_con[parent], _con[child]))
				{
					std::swap(_con[child], _con[parent]);
					parent=child;
					child = parent * 2 + 1;
				}
				else
				{
					break;
				}
			}
		}
		void pop()
		{
			//交换首尾元素
			std::swap(_con[0], _con[_con.size() - 1]);
			//删除尾元素
			_con.pop_back();
			//向下调整
			adjust_down(0);
		}
		T& top()
		{
			return _con[0];
		}
		bool empty()
		{
			return _con.empty();
		}
		size_t size()
		{
			return _con.size();
		}
		//成员变量
	private:
		Container _con;
		Compare _com;
	};

}

int main()
{
	int a[] = { 4,6,7,1,9,3,2,8,5 };
	lbk::priority_queue<int,vector<int>,greater<int>> pq(a,a+sizeof(a)/sizeof(a[0]));
	while (!pq.empty())
	{
		cout << pq.top() << ' ';
		pq.pop();
	}
	cout << endl;
	return 0;
}

//#include <vector>
//#include <queue>
//void TestPriorityQueue()
//{
//	 默认情况下，创建的是大堆，其底层按照小于号比较
//	vector<int> v{3, 2, 7, 6, 0, 4, 1, 9, 8, 5};
//	priority_queue<int> q1;
//	for (auto& e : v)
//		q1.push(e);
//	while (!q1.empty())
//	{
//		cout << q1.top() << " ";
//		q1.pop();
//	}//9 8 7 6 5 4 3 2 1 0
//	cout << endl;
//	 如果要创建小堆，将第三个模板参数换成greater比较方式
//	priority_queue<int, vector<int>, greater<int>> q2(v.begin(), v.end());
//	while (!q2.empty())
//	{
//		cout << q2.top() << " ";
//		q2.pop();
//	}//0 1 2 3 4 5 6 7 8 9
//}
//int main()
//{
//	TestPriorityQueue();
//}