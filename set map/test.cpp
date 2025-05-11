#define _CRT_SECURE_NO_WARNINGS
#include "set.cpp"
#include "map.cpp"
#include <set>

int main()
{
	//lbk::set<int> s;
	lbk::map<int, int> m;
	vector<int> v = { 1,9,5,6,4,8,2,7,3 };
	for (auto e : v)
	{
		m.insert(make_pair(e, 0));
		//s.insert(e);
	}
	//s.InOrder();
	m.InOrder();
	m[1] = 5;
	cout << m[1];
	return 0;
}