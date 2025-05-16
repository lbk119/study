#define _CRT_SECURE_NO_WARNINGS
#include"unordered_set.cpp"
int main()
{
	lbk::unordered_set<int> hash1;
	hash1.insert(1);
	hash1.insert(2);
	hash1.insert(3);
	hash1.insert(4);
	hash1.insert(5);
	for (auto& e : hash1)
		cout << e << " ", hash1.erase(e);
	for (auto& e : hash1)
		cout << e << " ";
	return 0;
}