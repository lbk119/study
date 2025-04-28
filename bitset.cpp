#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<bitset>
#include<vector>
using namespace std;
namespace lbk
{
	template<size_t N>
	class bitset
	{
	public:
		bitset()
		{
			_bit.resize(N / 32 + 1,0);
			_count = 0;
		}
		size_t size()
		{
			return N;
		}
		size_t count()
		{
			int bitCnttable[256] = {
				0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2,
				3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3,
				3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3,
				4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4,
				3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5,
				6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4,
				4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5,
				6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5,
				3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3,
				4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6,
				6, 7, 6, 7, 7, 8 };
			for (auto e : _bit)
			{
				for (int i = 0; i < 4; i++)
				{
					unsigned char c = e;
					_count += bitCnttable[c];
					e >>= 8;
				}
			}
			return _count;
		}
		bitset& set(size_t x)
		{
			int i = x / 32;
			int j = x % 32;
			_bit[i] |= (1 << j);
			return *this;
		}
		bitset& reset(size_t x)
		{
			int i = x / 32;
			int j = x % 32;
			_bit[i] &= (~(1 << j));
			return *this;
		}
		bool test(size_t x)
		{
			int i = x / 32;
			int j = x % 32;
			return _bit[i] & (1 << j);
		}
	private:
		vector<int> _bit;
		size_t _count;
	};
}
int main()
{
	lbk::bitset<100> b;
	cout << b.test(1) << endl;
	b.set(2);
	b.set(3);
	b.reset(3);
	cout << b.test(2) << endl;
	cout << b.test(3) << endl;

	return 0;
}