#include <stdio.h>

#include "tree.h"

static int SeekItem(Node * pn, Node * root);					// 查找插入的对象在树中的位置
static void InOrder(Node * pn, void(*pfun)(Item item));			// 遍历树并对每个节点应用函数
static void DelAllNode(Node * pn);								// 清除所有的节点

void InitializeTree(Tree * ptree)
{
	// 初始化树
	ptree->root = NULL;
	ptree->size = 0;
}

bool TreeIsFull(const Tree * ptree)
{
	// 返回树是否已满
	return ptree->size == MAXITEMS;
}

bool TreeIsEmpty(const Tree * ptree)
{
	// 返回树是否为空
	return (ptree->root == NULL);
}

int TreeItemCount(const Tree * ptree)
{
	// 返回树的长度
	return ptree->size;
}

bool AddItem(Item item, Tree * ptree)
{
	// 在树中新增节点
	Node * pn;
	if (TreeIsFull(ptree))
	{
		// 在树已满的情况下无法新增节点
		fprintf(stderr, "Tree is full!\n");
		return false;
	}
	pn = (Node *)malloc(sizeof(Node));
	pn->item = item;
	if (TreeIsEmpty(ptree))
	{
		// 为空树设置根节点
		ptree->root = pn;
		pn->parent = pn->left = pn->right = NULL;
	}
	else
		// 在合适的位置插入新节点
		SeekItem(pn, ptree->root);

	ptree->size++;

	return true;
}

bool InTree(Item item, Tree * ptree)
{
	// 检查目标对象是否在树中
	if (TreeIsEmpty(ptree))
		// 空树中无对象
		return false;
	Node * pn;
	pn = FindItem(item, ptree->root);

	// 没有找到对象返回false，找到对象返回true 并递增对象中的count（此处违反ADT 设计原则）
	if (pn == NULL)
		return false;
	else
	{
		pn->item.count++;
		return true;
	}
}

static int SeekItem(Node * pn, Node * root)
{
	// 递归查找新对象在树中的位置
	int cmp = strcmp(pn->item.word, root->item.word);
	if (cmp < 0)
	{
		if (root->left == NULL)
		{
			pn->parent = root;
			root->left = pn;
			pn->left = pn->right = NULL;
		}
		else
			SeekItem(pn, root->left);
	}
	else if (cmp > 0)
	{
		if (root->right == NULL)
		{
			pn->parent = root;
			root->right = pn;
			pn->left = pn->right = NULL;
		}
		else
			SeekItem(pn, root->right);
	}
	else
		return 1;

	return 0;
}

Node * FindItem(Item item, Node * root)
{
	// 根据目标对象返回相应节点的指针
	// 根据已排序树的属性（左小右大），顺着插入对象时的路径查找对象
	Node * pn;
	pn = root;
	int cmp = 0;
	while (pn != NULL)
	{
		cmp = strcmp(item.word, pn->item.word);
		if (cmp == 0)
			break;
		if (cmp < 0)
			pn = pn->left;
		else
			pn = pn->right;
	}

	return pn;
}

void Traverse(const Tree * ptree, void(*pfun)(Item item))
{
	// 对树中的每个节点应用函数
	if(ptree != NULL)
		InOrder(ptree->root, pfun);
}

static void InOrder(Node * pn, void(*pfun)(Item item))
{
	// 递归遍历树中的每个节点，并应用函数
	if (pn != NULL)
	{
		InOrder(pn->left, pfun);
		(*pfun)(pn->item);
		InOrder(pn->right, pfun);
	}
}

void DelTree(Tree * ptree)
{
	// 清空树
	Node * pn;
	pn = ptree->root;
	DelAllNode(pn, ptree);
}

static void DelAllNode(Node * pn)
{
	// 递归释放所有的节点
	Node * temp;
	if (pn != NULL)
	{
		temp = pn->right;
		DelAllNode(pn->left);
		free(pn);
		DelAllNode(temp);
	}
}
