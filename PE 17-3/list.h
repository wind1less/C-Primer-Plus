#ifndef LIST_H_
#define LIST_H_

#include <stdbool.h>

#define TSIZE 45
#define MAXSIZE 100

struct film {
	char title[TSIZE];
	int rating;
};

typedef struct film Item;

typedef struct list
{
	Item entries[MAXSIZE];
	int items;
} List;

// 初始化一个链表
void InitializeList(List * plist);

// 返回链表是否为空
bool ListIsEmpty(const List * plist);

// 返回链表是否已满
bool ListIsFull(const List * plist);

// 返回链表中的项数
unsigned int ListItemCount(const List * plist);

// 在链表的末尾添加项，返回是否添加成功
bool AddItem(Item item, List * plist);

// 遍历链表，对链表中的每个项作用pfun函数
void Traverse(const List * plist, void(*pfun)(Item item));

// 清空链表内容，释放为链表分配的内存
void EmptyTheList(List * plist);

#endif
