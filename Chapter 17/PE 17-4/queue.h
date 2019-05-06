#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdbool.h>

// 定义队列内的数据类型
typedef struct item
{
	long arrive;                // 顾客加入队列的时间
	int processtime;            // 顾客咨询花费的时间
	int line;                   // 顾客被分配到的队列
} Item;

#define MAXQUEUE 10             // 队列容量

typedef struct node {
	Item item;
	struct node * next;
} Node;					        // 队列中的每个元素包含当前对象的信息和下个元素的地址

typedef struct quque {
	Node * front;		        // 指向队列首项的指针
	Node * rear;		        // 指向队列尾项的指针
	int items;			        // 队列中的项数
} Queue;

// 初始化队列
void InitializeQueue(Queue * pq);

// 检查队列是否已满
bool QueueIsFull(const Queue * pq);

// 检查队列是否为空
bool QueueIsEmpty(const Queue * pq);

// 确定队列中的项数
int QueueItemCount(const Queue * pq);

// 在队列末尾添加项
bool EnQueue(Item item, Queue * pq);

// 从队列的开头删除项
bool DeQueue(Item * pitem, Queue * pq);

// 清空队列
void EmptyTheQueue(Queue * pq);

#endif
