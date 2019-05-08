#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "标头.h"

typedef struct pair {
	Trnode * parent;
	Trnode * child;
} Pair;

static Trnode * MakeNode(const Item * pi);							// 根据传入的对象创建一个新节点
static bool ToLeft(const Item * i1, const Item * i2);				// 比较目标对象与当前节点
static void AddNode(Trnode * new_node, Trnode * root);				// 添加一个节点
static void InOrder(const Trnode * root, void(*pfun)(Item item));	// 递归遍历树中所有节点，并应用函数	
static Pair SeekItem(const Item * pi, const Tree * ptree);			// 找到目标节点的位置，返回目标节点的父节点用于定位
static void DeleteNode(Trnode **ptr);								// 删除一个节点，并处理该节点的子节点
static void DeleteAllNodes(Trnode * ptr);							// 删除所有的节点

void InitializeTree(Tree * ptree)
{
	// 初始化一个树
	ptree->root = NULL;
	ptree->size = 0;
}

bool TreeIsEmpty(const Tree * ptree)
{
	// 确定树是否为空
	return (ptree->root == NULL);
}

bool TreeIsFull(const Tree * ptree)
{
	// 确定树是否已满
	return (ptree->size == MAXITEMS);
}

int TreeItemCount(const Tree * ptree)
{
	// 确定树的项数
	return ptree->size;
}

bool AddItem(const Item * pi, Tree * ptree)
{
	// 在树中添加一个项
	Trnode * new_node;

	if (TreeIsFull(ptree))
	{
		fprintf(stderr, "Tree is full\n");
		return false;
	}
	new_node = SeekItem(pi, ptree).child;
	if (new_node != NULL)
	{
    // 如果目标宠物名已存在，则在已存在的节点内增加宠物类型数组
		new_node->item.kindcount++;
		strcpy(new_node->item.petkind[new_node->item.kindcount], pi->petkind[0]);
	}
	else
	{
    // 如果目标宠物名不存在，则新增一个节点
		new_node = MakeNode(pi);
		if (new_node == NULL)
		{
			fprintf(stderr, "couldn't create node\n");
			return false;
		}

		// 通过前置条件
		ptree->size++;
		if (TreeIsEmpty(ptree))
			ptree->root = new_node;
		else
			AddNode(new_node, ptree->root);
	}

	return true;
}

bool InTree(const Item * pi, const Tree * ptree)
{
	// 在树中查找一个项

	Trnode * pn;
	pn = SeekItem(pi, ptree).child;
	if (pn == NULL)
		return false;
	else
	{
		for (int i = 0; i <= pn->item.kindcount; i++)
		{
			if (strcmp(pn->item.petkind[i], pi->petkind[0]) == 0)
				return true;
		}
	}
	return false;
}

bool DeleteItem(const Item * pi, Tree * ptree)
{
	// 从树中删除一个项
	Pair look;
	Trnode * pn;
	look = SeekItem(pi, ptree);
	
	pn = look.child;
	if (pn == NULL)
		return false;

	// 判断需要删除petkind 还是删除trnode
	if (pn->item.kindcount == 0)
	{
    // 当节点内仅有一个宠物类型时，删除节点
		if (look.parent == NULL)
			DeleteNode(&ptree->root);
		else if (look.parent->left == look.child)
			DeleteNode(&look.parent->left);
		else
			DeleteNode(&look.parent->right);
		ptree->size--;
	}
	else
	{
    // 当节点内有多个宠物类型时，找到数组内的目标类型，删除目标类型并移动其余数组元素
		int del = -1;
		for (int i = 0; i <= pn->item.kindcount; i++)
		{
			if (strcmp(pn->item.petkind[i], pi->petkind[0]) == 0)
			{
				del = i;
				break;
			}
		}
		if (del >= 0)
		{
			for (int i = del; i <= pn->item.kindcount; i++)
			{
				strcpy(pn->item.petkind[i], pn->item.petkind[i + 1]);
			}
			pn->item.kindcount--;
			return true;
		}
	}

	return false;

}

void Traverse(const Tree * ptree, void(*pfun)(Item item))
{
	// 把函数应用于树中的每一项
	if (ptree != NULL)
		InOrder(ptree->root, pfun);
}

void DeleteAll(Tree * ptree)
{
	// 删除树中的所有内容
	if (ptree != NULL)
		DeleteAllNodes(ptree->root);
	ptree->root = NULL;
	ptree->size = 0;
}

// 局部函数

static void InOrder(const Trnode * root, void(*pfun)(Item item))
{
	if (root != NULL)
	{
		InOrder(root->left, pfun);
		(*pfun)(root->item);
		InOrder(root->right, pfun);
	}
}

static void DeleteAllNodes(Trnode * root)
{
	Trnode * pright;

	if (root != NULL)
	{
		pright = root->right;
		DeleteAllNodes(root->left);
		free(root);
		DeleteAllNodes(pright);
	}
}

static void AddNode(Trnode * new_node, Trnode * root)
{
	if (ToLeft(&new_node->item, &root->item))
	{
		if (root->left == NULL)
			root->left = new_node;
		else
			AddNode(new_node, root->left);
	}
	
	// 此处调换ToLeft 函数两个参数传入的顺序，即当做ToRight 函数来使用
	else if (ToLeft(&root->item, &new_node->item))
	{
		if (root->right == NULL)
			root->right = new_node;
		else
			AddNode(new_node, root->right);
	}
	else
	{
		fprintf(stderr, "location error in AddNode() \n");
		exit(1);
	}
}

static bool ToLeft(const Item * i1, const Item * i2)
{
	int comp1;
	
	if ((comp1 = strcmp(i1->petname, i2->petname)) < 0)
		return true;
	//else if (comp1 == 0 && strcmp(i1->petkind, i2->petkind) < 0)
	//	return true;
	else
		return false;
}

static Trnode * MakeNode(const Item * pi)
{
	Trnode * new_node;

	new_node = (Trnode *)malloc(sizeof(Trnode));
	if (new_node != NULL)
	{
		new_node->item = *pi;
		new_node->left = new_node->right = NULL;
	}

	return new_node;
}

static Pair SeekItem(const Item * pi, const Tree * ptree)
{
	Pair look;
	look.parent = NULL;
	look.child = ptree->root;

	if (look.child == NULL)
		return look;

	// 如果树中已经存在目标节点，child 指向目标节点
	// 如果树中不存在目标节点，child 指向NULL，parent 指向目标节点的理论父节点
	while (look.child != NULL)
	{
		if (ToLeft(pi, &(look.child->item)))
		{
			look.parent = look.child;
			look.child = look.child->left;
		}
		else if (ToLeft(&(look.child->item), pi))
		{
			look.parent = look.child;
			look.child = look.child->right;
		}
		else
			break;
	}

	return look;
}

static void DeleteNode(Trnode ** ptr)
{
	// ptr 是指向目标节点的父节点指针成员的地址
	Trnode * temp;
	 
	// 被删除的节点只有一个子节点或无子节点的情况
	if ((*ptr)->left == NULL)
	{
		temp = *ptr;
		*ptr = (*ptr)->right;
		free(temp);
	}
	else if ((*ptr)->right == NULL)
	{
		temp = *ptr;
		*ptr = (*ptr)->left;
		free(temp);
	}

	// 被删除的节点有两个子节点的情况
	else {
		// 找到重新连接右子树的位置
		for (temp = (*ptr)->left; temp->right != NULL; temp = temp->right)
			continue;
		temp->right = (*ptr)->right;
		temp = *ptr;
		*ptr = (*ptr)->left;
		free(temp);
	}
}
