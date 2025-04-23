#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
typedef int LTDataType;
//双向带头循坏链表
typedef struct Node
{
	LTDataType data;
	struct Node* pre;
	struct Node* next;
}Node;
//初始化头指针
Node* LTInit()
{
	Node* head = (struct Node*)malloc(sizeof(struct Node));
	head->pre = head;
	head->next = head;
	return head;
}
//创建结点
Node* CreateNode(LTDataType data)
{
	Node* newnode = (struct Node*)malloc(sizeof(struct Node));
	assert(newnode);
	newnode->data = data;
	return newnode;
}
//头插法
void LTPushFront(Node* phead,LTDataType data)
{
	Node* newnode = CreateNode(data);
	Node* pheadnext = phead->next;
	phead->next = newnode;
	newnode->pre = phead;
	newnode->next = pheadnext;
	pheadnext->pre = newnode;
}
//尾插法
void LTPushBack(Node* phead, LTDataType data)
{
	Node* newnode = CreateNode(data);
	Node* tail = phead->pre;
	phead->pre = newnode;
	newnode->next = phead;
	newnode->pre = tail;
	tail->next = newnode;
}
void Print(Node* phead)
{
	Node* cur = phead->next;
	printf("head<==>");
	while (cur != phead)
	{
		printf("%d<==>", cur->data);
		cur = cur->next;
	}
	printf("head\n");
}
//判空函数
bool LTEmpty(Node* phead)
{
	return (phead->next == phead);
}
//头删
void LTPopFront(Node* phead)
{
	assert(phead);
	//断言链表不为空
	assert(!LTEmpty(phead));
	Node* del = phead->next;
	Node* delnext = del->next;
	free(del);
	phead->next = delnext;
	delnext->pre = phead;
}
//尾删
void LTPopBack(Node* phead)
{
	assert(phead);
	//断言链表不为空
	assert(!LTEmpty(phead));
	Node* tail = phead->pre;
	Node* tailpre = tail->pre;
	free(tail);
	tailpre->next = phead;
	phead->pre = tailpre;
}
//查找函数
Node* LTFind(Node* phead, LTDataType data)
{
	Node* cur = phead->next;
	while (cur != phead)
	{
		if (cur->data == data)
		{
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}
//在pos位置后面插入
void LTInsert(Node* pos,LTDataType data)
{
	assert(pos);
	Node* newnode = CreateNode(data);
	Node* posnext = pos->next;
	pos->next = newnode;
	newnode->pre = pos;
	newnode->next = posnext;
	posnext->pre = newnode;
}
//可以通过LTInsert函数来快速实现头插函数和尾插函数
void LTPushFront1(Node* phead, LTDataType data)
{
	LTInsert(phead, data);
}
void LTPushBack1(Node* phead, LTDataType data)
{
	Node* tail = phead->pre;
	LTInsert(tail, data);
}
//删除pos位置的结点
void LTErase(Node* pos)
{
	assert(pos);
	Node* pospre = pos->pre;
	Node* posnext = pos->next;
	free(pos);
	pospre->next = posnext;
	posnext->pre = pospre;
}
//可以通过LTErase函数来快速实现头删函数和尾删函数
void LTPopFront1(Node* phead)
{
	LTErase(phead->next);
}
void LTPopBack1(Node* phead)
{
	LTErase(phead->pre);
}
void test1()
{
	 Node* head = LTInit();
	 LTPushFront(head, 1);
	 LTPushFront(head, 2);
	 LTPushFront(head, 3);
	 Print(head);
	 LTPushBack(head, 4);
	 LTPushBack(head, 5);
	 LTPushBack(head, 6);
	 Print(head);
	 LTPopFront(head);
	 LTPopFront(head);
	 Print(head);
	 LTPopBack(head);
	 LTPopBack(head);
	 Print(head);
	 Node* pos = LTFind(head, 4);
	 LTInsert(pos, 5);
	 LTInsert(pos, 6);
	 Print(head);
	 LTErase(pos);
	 Print(head);
	 LTPushFront1(head, 9);
	 LTPushBack1(head, 8);
	 Print(head);
	 LTPopFront1(head);
	 LTPopBack1(head);
	 Print(head);

}
int main()
{
	test1();
	return 0;
}