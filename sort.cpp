#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include<stdlib.h>
#include<time.h>
#include<stack>
using namespace std;
void Print(int* a,int n)
{
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl;
}
// ֱ�Ӳ�������
void InsertSort(int* a, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int end = i;
		int tmp = a[end + 1];
		while (end >= 0)
		{
			if (a[end] > tmp)
			{
				//��a[end]����
				a[end + 1] = a[end];
				end--;
			}
			//�ҵ������λ��
			else
			{
				break;
			}
		}
		a[end+1] = tmp;
	}
}

// ϣ������
void ShellSort(int* a, int n)
{
	int gap = n;
	while (gap > 1)
	{
		gap=gap/3+1;
		for (int i = 0; i < n - gap; i++)
		{
			int end = i;
			int tmp = a[end + gap];
			while (end >= 0)
			{
				if (a[end] > tmp)
				{
					a[end + gap] = a[end];
					end -= gap;
				}
				else
				{
					break;
				}
			}
			a[end + gap] = tmp;
		}
	}
}
// ֱ��ѡ������
void SelectSort(int* a, int n)
{
	int begin = 0, end = n - 1;
	int maxi = 0, mini = 0;
	while (begin < end)
	{
		for (int i = begin + 1; i < end; i++)
		{
			if (a[i] > a[maxi])
			{
				maxi = i;
			}
			if (a[i] < a[mini])
			{
				mini = i;
			}
		}
		swap(a[begin], a[mini]);
		//�������λ����beginλ��
		//˵��min�Ǻ����Ľ���λ��
		//���ʱ��max��λ�þͷ����˱任
		//max�䵽��min��λ��
		//����Ҫ����max��λ��
		if (maxi == begin)
		{
			maxi = mini;
		}
		swap(a[end], a[maxi]);
		begin++;
		end--;
	}
}


//������
// ���򣬽����
//���µ����㷨����
void Adjustdown(int* a, int parent, int n)
{
	int child = parent * 2 + 1;
	while (child<n)
	{
		if (child + 1 < n && a[child] < a[child + 1])
		{
			child++;
		}
		if (a[child] > a[parent])
		{
			swap(a[child], a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}
void HeapSort(int* a, int n)
{
	//�����
	for (int i = (n - 1 - 1) / 2; i >= 0; i--)
	{
		Adjustdown(a, i, n);
	}
	int end = n - 1;
	while (end > 0)
	{
		swap(a[0], a[end]);
		//ѡ���δ��
		Adjustdown(a, 0, end);
		end--;
	}
}
// ð������
void BubbleSort(int* a, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i-1; j++)
		{
			if (a[j] > a[j + 1])
			{
				swap(a[j], a[j + 1]);
		    }
		}
	}
}

//����
// ��������ݹ�ʵ��
// ��������hoare�汾
int PartSort1(int* a, int left, int right)
{
	int keyi = left;
	while (left < right)
	{
		//һ��Ҫ���ұ����ߣ�����ʱ��ֵ�ű�keyҪС
		while (left < right && a[right] >= a[keyi])
		{
			right--;
		}
		while (left < right&&a[left] <= a[keyi])
		{
			left++;
		}
		
		swap(a[left], a[right]);
	}
	swap(a[left], a[keyi]);
	return left;
}
// ���������ڿӷ�
int PartSort2(int* a, int left, int right)
{
	int key = a[left];
	while (left < right)
	{
		while (left < right&&a[right] >= key)
		{
			right--;
		}
		swap(a[left], a[right]);
		while (left < right && a[left] <= key)
		{
			left++;
		}
		swap(a[left], a[right]);
	}
	a[left] = key;
	return left;
}
// ��������ǰ��ָ�뷨
int PartSort3(int* a, int left, int right)
{
	int keyi=left,pre = left, cur = left + 1;
	while (cur <= right)
	{
		if (a[cur] <= a[keyi]&&++pre!=cur)
		{
			swap(a[pre], a[cur]);
		}
		cur++;
	}
	swap(a[keyi], a[pre]);
	return pre;
}
int GetMid(int* arr,int a, int b, int c)
{
	int max1 = max(arr[a], arr[b]);
	int max2 = max(arr[b], arr[c]);
	int max3 = max(max1, max2);
	if (max3 == arr[a])
	{
		return a;
	}
	else if (max3 == arr[b])
	{
		return b;
	}
	else
	{
		return c;
	}
}
void QuickSort(int* a, int left, int right)
{
	if (left >= right)
	{
		return;
	}
	//�ݹ鵽С��������ʱ�����Կ���ʹ�ò�������
	if (right - left <= 10)
	{
		InsertSort(a + left, right);
	}
	//���ȡ����
	int randi = rand() % (right - left+1) + left;
	swap(a[left], a[randi]);

	//����ȡ�з�
	int mid = left + (right - left) / 2;
	int tmp = GetMid(a,left, mid, right);
	swap(a[tmp], a[left]);

	int begin = left, end = right;
	int keyi = left;

	//keyi = PartSort1(a,left,right);
	//keyi = PartSort2(a,left,right);
	keyi = PartSort3(a,left,right);

	QuickSort(a, begin, keyi - 1);
	QuickSort(a, keyi + 1,end);
}

// �������� �ǵݹ�ʵ��
void QuickSortNonR(int* a, int left, int right)
{
	stack<int> st;
	st.push(right);
	st.push(left);
	while (!st.empty())
	{
		int l = st.top();
		st.pop();
		int r = st.top();
		st.pop();
		if (l >= r)
		{
			continue;
		}
		int keyi=PartSort3(a, l, r);
		st.push(r);
		st.push(keyi + 1);
		st.push(keyi - 1);
		st.push(l);
	}
}

//�鲢����ݹ�ʵ��
void _MergeSort(int* a, int left,int right)
{
	if (left >= right)
	{
		return;
	}
	int mid = left + (right - left) / 2;
	_MergeSort(a, left, mid);
	_MergeSort(a, mid + 1, right);

	int begin1 = left, end1 = mid;
	int begin2 = mid + 1, end2 = right;
	int len = right - left + 1;
	int* tmp = new int(len);
	int i = 0;
	while (begin1 <= end1 && begin2 <= end2)
	{
		while (begin1 <= end1 && a[begin1]<=a[begin2])
		{
			tmp[i++] = a[begin1++];
		}
		while (begin2 <= end2 && a[begin1] > a[begin2])
		{
			tmp[i++] = a[begin2++];
		}
	}
	while (begin1 <= end1)
	{
		tmp[i++] = a[begin1++];
	}
	while (begin2 <= end2)
	{
		tmp[i++] = a[begin2++];
	}
	memcpy(a + left, tmp, sizeof(int) * len);
}
void MergeSort(int* a, int n)
{
	_MergeSort(a, 0, n - 1);
}

// �鲢���� �ǵݹ�ʵ��
void MergeSortNonR(int* a, int n)
{
	for (int count = 1; count <n; count *= 2)
	{
		for (int j=0;j<n;j+=2*count)
		{
			int begin1 = j, end1 =begin1+count-1;
			int begin2 = end1+1, end2 = begin2+count-1;
			//Խ������
			if (end1 >= n||begin2>=n)
			{
				break;
			}
			if (end2>=n)
			{
				end2 = n - 1;
			}
			int len = end2-begin1 + 1;
			int* tmp = new int(len);
			int i = 0;
 			while (begin1 <= end1 && begin2 <= end2)
			{
				while (begin1 <= end1 && a[begin1] <= a[begin2])
				{
					tmp[i++] = a[begin1++];
				}
				while (begin2 <= end2 && a[begin1] > a[begin2])
				{
					tmp[i++] = a[begin2++];
				}
			}
			while (begin1 <= end1)
			{
				tmp[i++] = a[begin1++];
			}
			while (begin2 <= end2)
			{
				tmp[i++] = a[begin2++];
			}
			memcpy(a + j, tmp, sizeof(int) * len);
		}
	}
}
int main()
{
	int a[] = { 5,9,1,6,8,2,4,7,3 };
	int sz = sizeof(a) / sizeof(a[0]);
	Print(a, sz);
	//InsertSort(a, sz);
	//ShellSort(a, sz);
	//SelectSort(a, sz);
	//HeapSort(a, sz);
	//BubbleSort(a, sz);
	//QuickSort(a, 0, sz-1);
	//QuickSortNonR(a, 0, sz - 1);
	//MergeSort(a, sz);
	MergeSortNonR(a, sz);
	Print(a, sz);

	return 0;
}