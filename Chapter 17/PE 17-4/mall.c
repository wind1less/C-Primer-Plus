#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

static void CopyToNode(Item item, Node * pn);
static void CopyToItem(Node * pn, Item * pi);

void InitializeQueue(Queue * pq)
{
	// 初始化队列
	pq->front = pq->rear = NULL;
	pq->items = 0;
}

bool QueueIsFull(const Queue * pq)
{
	// 检查队列是否已满
	return pq->items == MAXQUEUE;
}

bool QueueIsEmpty(const Queue * pq)
{
	// 检查队列是否为空
	return pq->items == 0;
}

int QueueItemCount(const Queue * pq)
{
	// 确定队列中的项数
	return pq->items;
}

bool EnQueue(Item item, Queue * pq)
{
	// 在队列末尾添加项
	Node * pnew;

	if (QueueIsFull(pq))
		return false;
	pnew = (Node *)malloc(sizeof(Node));
	if (pnew == NULL)
	{
		fprintf(stderr, "Unable to allocate memory!\n");
		exit(1);
	}
 	CopyToNode(item, pnew);
	pnew->next = NULL;
	if (QueueIsEmpty(pq))
		pq->front = pnew;
	else
		pq->rear->next = pnew;
	pq->rear = pnew;
 	pq->items++;

	return true;
 }

bool DeQueue(Item * pitem, Queue * pq)
{
	// 从队列的开头删除项
	Node * pt;


	if (QueueIsEmpty(pq))
		return false;
	CopyToItem(pq->front, pitem);
	pt = pq->front;
	pq->front = pq->front->next;
	free(pt);
	pq->items--;
	if (pq->items == 0)
		pq->rear = NULL;

	return true;
}

void EmptyTheQueue(Queue * pq)
{
	// 清空队列
	Item dummy;
	while (!QueueIsEmpty(pq))
		DeQueue(&dummy, pq);
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
