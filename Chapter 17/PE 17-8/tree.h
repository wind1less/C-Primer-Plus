#ifndef _TREE_H_
#define _TREE_H_

#include <stdbool.h>

#define SLEN 20
#define MAXKIND 20

typedef char Petkind[SLEN];

typedef struct item {
	char petname[SLEN];         // 宠物名  
	Petkind petkind[MAXKIND];   // 同名下的宠物类型
	int kindcount;              // 同名下宠物类型计数
} Item;

#define MAXITEMS 10

typedef struct trnode{
	Item item;
	struct trnode * left;
	struct trnode * right;
} Trnode;

typedef struct tree{
	Trnode * root;
	int size;
} Tree;

// 初始化一个树
void InitializeTree(Tree * ptree);

// 确定树是否为空
bool TreeIsEmpty(const Tree * ptree);

// 确定树是否已满
bool TreeIsFull(const Tree * ptree);

// 确定树的项数
int TreeItemCount(const Tree * p5tree);

// 在树中添加一个项
bool AddItem(const Item * pi, Tree * ptree);

// 在树中查找一个项
bool InTree(const Item * pi, const Tree * ptree);

// 从树中删除一个项
bool DeleteItem(const Item * pi, Tree * ptree);

// 把函数应用于树中的每一项
void Traverse(const Tree * ptree, void(*pfun)(Item item));

// 删除树中的所有内容
void DeleteAll(Tree * ptree);

#endif
