#ifndef _STACK_H_
#define _STACK_H_

#include <stdbool.h>

// 定义栈内的数据类型
typedef char item;

typedef item Item;

#define MAXSTACK 20	            // 栈容量

typedef struct node {
	Item item;
	struct node * prev;
} Node;                         // 栈中的每个元素包含当前对象的信息和下个元素的地址

typedef struct stack {
	//Node * front;             // 指向栈首项的指针
	Node * rear;                // 指向栈尾项的指针
	int items;                  // 栈中的项数
} Stack;

// 初始化栈
void InitializeStack(Stack * ps);

// 检查栈是否已满
bool StackIsFull(const Stack * ps);

// 检查栈是否为空
bool StackIsEmpty(const Stack * ps);

// 确定栈中的项数
int StackItemCount(const Stack * ps);

// 在栈末尾添加项
bool PushStack(Item item, Stack * ps);

// 从栈的末尾删除项
bool PopStack(Item * pitem, Stack * ps);

// 清空栈
void EmptyTheStack(Stack * ps);

#endif
