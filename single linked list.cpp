#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
typedef int MyDataType;
typedef struct SLTNode
{
	MyDataType data;
	struct SLTNode* next;
}SLTNode;
//创建结点
SLTNode* CreateNode(MyDataType data)
{
	SLTNode* newnode = (SLTNode*)malloc(sizeof(SLTNode));
	assert(newnode);
	newnode->data = data;
	newnode->next = NULL;
	return newnode;
}
//打印
void SLTPrint(SLTNode* head)
{
	SLTNode* cur = head;
	while (cur)
	{
		printf("%d->", cur->data);
		cur = cur->next;
	}
	printf("NULL\n");
}
//头插(优)
void SLTPushFront(SLTNode** pphead, MyDataType data)
{
	SLTNode* newnode = CreateNode(data);
	newnode->next = *pphead;
	*pphead = newnode;
}
//尾插
void SLTPushBack(SLTNode** pphead, MyDataType data)
{
	SLTNode* newnode = CreateNode(data);
	//判断一个结点也没有时，需要改变头指针，所以需要传二级指针
	if (*pphead == NULL)
	{
		*pphead = newnode;
	}
	else
	{
		//找尾节点
		SLTNode* tail = *pphead;
		while (tail->next)
		{
			tail = tail->next;
		}
		tail->next = newnode;
	}
}
//头删
void SLTPopFront(SLTNode** head)
{
	//空
	assert(*head);
	//一个结点
	if ((*head)->next == NULL)
	{
		free(*head);
		*head = NULL;
	}
	//多个结点
	else
	{
		SLTNode* del = *head;
		*head = (*head)->next;
		free(del);
		del = NULL;
	}
}
//尾删
void SLTPopBack(SLTNode** head)
{
	//空
	assert(*head);
	//一个结点
	if ((*head)->next == NULL)
	{
		free(*head);
		*head = NULL;
	}
	//多个结点
	else
	{
		SLTNode* tail = *head;
		//找到尾结点的前一个结点
		while (tail->next->next)
		{
			tail = tail->next;
		}
		free(tail->next);
		tail->next = NULL;
	}
}
//寻找结点位置
SLTNode* SLTFind(SLTNode* phead,MyDataType data)
{
	SLTNode* cur = phead;
	while (cur->data != data)
	{
		cur = cur->next;
	}
	return cur;
}
//特定位置前插
void SLTInsertFront(SLTNode** pphead,SLTNode* pos, MyDataType data)
{
	assert(pos);
	//在第一个结点前插入，因为会改变头指针，为头插
	if ((*pphead) == pos)
	{
		SLTPushFront(pphead, data);
	}
	else
	{
		SLTNode* cur = *pphead;
		while (cur->next != pos)
		{
			cur = cur->next;
		}
		SLTNode* newnode = CreateNode(data);
		cur->next = newnode;
		newnode->next = pos;
	}
}
//特定位置后插(优)
void SLTInsertAfter(SLTNode* pos, MyDataType data)
{
	SLTNode* newnode = CreateNode(data);
	newnode->next = pos->next;
	pos->next = newnode;
}
//特定位置删除
void SLTErase(SLTNode** pphead,SLTNode* pos)
{
	//删除第一个结点时，需要改变头指针，为头删
	if (*pphead == pos)
	{
		*pphead = pos->next;
		free(pos);
	}
	else
	{
		SLTNode* cur = *pphead;
		while (cur->next != pos)
		{
			cur = cur->next;
		}
		cur->next = pos->next;
		free(pos);
	}
}
//销毁链表
void SLTDestroy(SLTNode** pphead)
{
	while(*pphead)
	{
		SLTNode* cur = (*pphead)->next;
		free(*pphead);
		*pphead = cur;
	} 
}
void SLTtest1()
{
	SLTNode* plist = NULL;
	SLTPushFront(&plist, 1);
	SLTPushFront(&plist, 2);
	SLTPushFront(&plist, 3);
	SLTPrint(plist);
	SLTPushBack(&plist, 4);
	SLTPushBack(&plist, 5);
	SLTPushBack(&plist, 6);
	SLTPrint(plist);
	SLTPopFront(&plist);
	SLTPopFront(&plist);
	SLTPrint(plist);
	SLTPopBack(&plist);
	SLTPopBack(&plist);
	SLTPrint(plist);
	SLTNode* p1 = SLTFind(plist, 4);
	SLTInsertFront(&plist, p1, 7);
	SLTInsertAfter(p1, 8);
	SLTPrint(plist);
	SLTErase(&plist, p1);
	SLTPrint(plist);
	SLTDestroy(&plist);
}
int main()
{
	SLTtest1();
	return 0;
}