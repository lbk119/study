#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<bitset>
using namespace std;
//哈希函数
struct BKDRHash
{
	size_t operator()(const string& s)
	{
		// BKDR
		size_t value = 0;
		for (auto ch : s)
		{
			value *= 31;
			value += ch;
		}
		return value;
	}
};
struct APHash
{
	size_t operator()(const string& s)
	{
		size_t hash = 0;
		for (long i = 0; i < s.size(); i++)
		{
			if ((i & 1) == 0)
				hash ^= ((hash << 7) ^ s[i] ^ (hash >> 3));
			else
				hash ^= (~((hash << 11) ^ s[i] ^ (hash >> 5)));
		}
		return hash;
	}
};
struct DJBHash
{
	size_t operator()(const string & s)
	{
		size_t hash = 5381;
		for (auto ch : s)
		{
			hash += (hash << 5) + ch;
		}
		return hash;
	}
};
//第一个参数为插入的个数，第二个参数为容器要开空间为插入个数的倍数大小，
//第三个参数为插入的元素类型，后三个参数为哈希函数
template<size_t N,size_t X = 5,class K = string,class Hash1= BKDRHash,
	class Hash2 = APHash, class Hash3 = DJBHash >
class BloomFilter
{
public:
	void set(const K& key)
	{
		size_t len = N * X;
		size_t index1 = Hash1()(key) % len;
		size_t index2 = Hash2()(key) % len;
		size_t index3 = Hash3()(key) % len;
		_bitset.set(index1);
		_bitset.set(index2);
		_bitset.set(index3);
	}
	bool test(const K& key)
	{
		size_t len = N * X;
		size_t index1 = Hash1()(key) % len;
		if (_bitset.test(index1) == false)
			return false;
		size_t index2 = Hash2()(key) % len;
		if (_bitset.test(index2) == false)
			return false;
		size_t index3 = Hash3()(key) % len;
		if (_bitset.test(index2) == false)
			return false;
		return true;
	}

private:
	bitset<N* X> _bitset;
};