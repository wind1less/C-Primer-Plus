#include <stdio.h>
#include <stdlib.h>

#include "list.h"

static void CopyToNode(Item item, Node * pnode);

void InitializeList(List * plist)
{
	//  把链表设置为空
	plist->head = plist->end = NULL;
}

bool ListIsEmpty(const List * plist)
{
	// 返回链表是否为空
	return (plist->head == NULL);
}

bool ListIsFull(void)
{
	// 返回链表是否已满
	Node * pt;
	bool full;

	pt = (Node *)malloc(sizeof(Node));
	full = (pt == NULL);
	free(pt);

	return full;
}

unsigned int ListItemCount(const List * plist)
{
	// 返回节点的数量
	unsigned int count = 0;
	Node * pnode = plist->head;

	while (pnode != NULL)
	{
		++count;
		pnode = pnode->next;
	}

	return count;
}

bool AddItem(Item item, List * plist)
{
	// 创建储存项的节点，并将其添加至链表末尾
	Node * pnew;
	Node * scan = plist->head;

	if (ListIsFull(plist))
		return false;

	pnew = (Node *)malloc(sizeof(Node));
	CopyToNode(item, pnew);
	pnew->next = NULL;
	
	if (scan == NULL)
		plist->head = plist->end = pnew;
	else
	{
		plist->end->next = pnew;
		plist->end = pnew;
		//while (scan->next != NULL)
		//	scan = scan->next;
		//scan->next = pnew;
		//plist->end = pnew;
	}

	return true;
}

void Traverse(const List * plist, void(*pfun)(Item item))
{
	// 访问每个节点并执行pfun 指向的函数
	Node * pnode = plist->head;

	while (pnode != NULL)
	{
		(*pfun)(pnode->item);
		pnode = pnode->next;
	}
}

void EmptyTheList(List * plist)
{
	// 释放内存，设置链表指针为NULL
	Node * psave;

	while (plist->head != NULL)
	{
		psave = plist->head->next;
		free(plist->head);
		plist->head = psave;
	}
}

static void CopyToNode(Item item, Node * pnode)
{
	// 把一个项拷贝到节点中
	pnode->item = item;
}
