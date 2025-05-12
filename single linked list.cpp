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
//�������
SLTNode* CreateNode(MyDataType data)
{
	SLTNode* newnode = (SLTNode*)malloc(sizeof(SLTNode));
	assert(newnode);
	newnode->data = data;
	newnode->next = NULL;
	return newnode;
}
//��ӡ
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
//ͷ��(��)
void SLTPushFront(SLTNode** pphead, MyDataType data)
{
	SLTNode* newnode = CreateNode(data);
	newnode->next = *pphead;
	*pphead = newnode;
}
//β��
void SLTPushBack(SLTNode** pphead, MyDataType data)
{
	SLTNode* newnode = CreateNode(data);
	//�ж�һ�����Ҳû��ʱ����Ҫ�ı�ͷָ�룬������Ҫ������ָ��
	if (*pphead == NULL)
	{
		*pphead = newnode;
	}
	else
	{
		//��β�ڵ�
		SLTNode* tail = *pphead;
		while (tail->next)
		{
			tail = tail->next;
		}
		tail->next = newnode;
	}
}
//ͷɾ
void SLTPopFront(SLTNode** head)
{
	//��
	assert(*head);
	//һ�����
	if ((*head)->next == NULL)
	{
		free(*head);
		*head = NULL;
	}
	//������
	else
	{
		SLTNode* del = *head;
		*head = (*head)->next;
		free(del);
		del = NULL;
	}
}
//βɾ
void SLTPopBack(SLTNode** head)
{
	//��
	assert(*head);
	//һ�����
	if ((*head)->next == NULL)
	{
		free(*head);
		*head = NULL;
	}
	//������
	else
	{
		SLTNode* tail = *head;
		//�ҵ�β����ǰһ�����
		while (tail->next->next)
		{
			tail = tail->next;
		}
		free(tail->next);
		tail->next = NULL;
	}
}
//Ѱ�ҽ��λ��
SLTNode* SLTFind(SLTNode* phead,MyDataType data)
{
	SLTNode* cur = phead;
	while (cur->data != data)
	{
		cur = cur->next;
	}
	return cur;
}
//�ض�λ��ǰ��
void SLTInsertFront(SLTNode** pphead,SLTNode* pos, MyDataType data)
{
	assert(pos);
	//�ڵ�һ�����ǰ���룬��Ϊ��ı�ͷָ�룬Ϊͷ��
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
//�ض�λ�ú��(��)
void SLTInsertAfter(SLTNode* pos, MyDataType data)
{
	SLTNode* newnode = CreateNode(data);
	newnode->next = pos->next;
	pos->next = newnode;
}
//�ض�λ��ɾ��
void SLTErase(SLTNode** pphead,SLTNode* pos)
{
	//ɾ����һ�����ʱ����Ҫ�ı�ͷָ�룬Ϊͷɾ
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
//��������
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