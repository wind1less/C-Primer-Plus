#include <stdio.h>
#include <stdlib.h>
//#include "list.h"
#include "标头.h"


void InitializeList(List * plist)
{
	//  把链表设置为空
	plist->items = 0;
}

bool ListIsEmpty(const List * plist)
{
	// 返回链表是否为空
	return (plist->items == 0);
}

bool ListIsFull(const List * plist)
{
	// 返回链表是否已满
	return (plist->items >= MAXSIZE -1);
}

unsigned int ListItemCount(const List * plist)
{
	// 返回节点的数量
	return plist->items;
}

bool AddItem(Item item, List * plist)
{
	// 创建储存项的节点，并将其添加至链表末尾
	if (ListIsFull(plist))
		return false;

	plist->entries[plist->items] = item;
	plist->items++;

	return true;
}

void Traverse(const List * plist, void(*pfun)(Item item))
{
	// 访问每个节点并执行pfun 指向的函数
	for (int i = 0; i < plist->items; i++)
		(*pfun)(plist->entries[i]);
}

void EmptyTheList(List * plist)
{
	// 释放内存，设置链表指针为NULL
	plist = NULL;
}
