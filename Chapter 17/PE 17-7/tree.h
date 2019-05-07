#ifndef _TREE_H_
#define _TREE_H_

#include <stdbool.h>

#define SLEN 15             // 存储单词的字符数组的长度
#define MAXITEMS 30000      // 树的节点上限

typedef struct item {
	char word[SLEN];	    // 该单词
	int count;			    // 该单词出现的次数
} Item;

typedef struct node{
	Item item;			        // 当前节点
	struct node * parent;		// 父节点
	struct node * left;		    // 左子节点
	struct node * right;		// 右子节点
} Node;

typedef struct tree {
	Node * root;
	int size;
} Tree;

void InitializeTree(Tree * ptree);								// 初始化树

bool TreeIsEmpty(const Tree * ptree);							// 返回树是否为空

bool TreeIsFull(const Tree * ptree);							// 返回树是否已满

int TreeItemCount(const Tree * ptree);							// 返回树的长度

void Traverse(const Tree * ptree, void(*pfun)(Item item));		// 对树中的每个节点应用函数

bool AddItem(Item item, Tree * ptree);							// 在树中新增节点

void DelTree(Tree * ptree);										// 清空树

bool InTree(Item item, Tree * ptree);							// 检查目标对象是否在树中

Node * FindItem(Item item, Node * root);						// 根据目标对象返回相应节点的指针
#endif
