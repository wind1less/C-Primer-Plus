#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

static void CopyToNode(Item item, Node * pn);
static void CopyToItem(Node * pn, Item * pi);

void InitializeStack(Stack * ps)
{
	// 初始化栈
	ps->rear = NULL;
	ps->items = 0;
}

bool StackIsFull(const Stack * ps)
{
	// 检查栈是否已满
	return ps->items == MAXSTACK;
}

bool StackIsEmpty(const Stack * ps)
{
	// 检查栈是否为空
	return ps->items == 0;
}

int StackItemCount(const Stack * ps)
{
	// 确定栈中的项数
	return ps->items;
}

bool PushStack(Item item, Stack * ps)
{
	// 在栈尾添加项
	Node * pnew;

	if (StackIsFull(ps))
		return false;
	pnew = (Node *)malloc(sizeof(Node));
	if (pnew == NULL)
	{
		fprintf(stderr, "Unable to allocate memory!\n");
		exit(1);
	}
 	CopyToNode(item, pnew);
	if (StackIsEmpty(ps))
		pnew->prev = NULL;
	else
		pnew->prev = ps->rear;
	ps->rear = pnew;
 	ps->items++;

	return true;
 }

bool PopStack(Item * pitem, Stack * ps)
{
	// 从栈尾删除项
	Node * pt;

	if (StackIsEmpty(ps))
		return false;
	CopyToItem(ps->rear, pitem);
	pt = ps->rear;
	ps->rear = ps->rear->prev;
	free(pt);
	ps->items--;


	return true;
}

void EmptyTheStack(Stack * ps)
{
	// 清空栈
	Item dummy;
	while (!StackIsEmpty(ps))
		PopStack(&dummy, ps);
}

// 局部函数

static void CopyToNode(Item item, Node * pn)
{
	pn->item = item;
}

static void CopyToItem(Node * pn, Item * pi)
{
	*pi = pn->item;
}
