// 修改宠物俱乐部程序，把所有同名的宠物都储存在同一个节点中。
// 当用户选择查找宠物时，程序应询问用户该宠物的名字，然后列出该名字的所有宠物（及其种类）。

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "标头.h"

char menu(void);                                // 显示菜单响应用户操作
void addpet(Tree * pt);                         // 执行用户操作添加宠物
void droppet(Tree * pt);                        // 执行用户操作删除宠物
void showpets(const Tree * pt);                 // 执行用户操作显示宠物列表
void findpet(const Tree * pt);                  // 执行用户操作查询宠物
void printitem(Item item);                      // 打印二叉树单个节点内的对象的信息
void uppercase(char * str);                     // 将字符串转为大写
char * s_gets(char * st, int n);                // 读取一行输入
void Ask_The_Pet(Item * item, char * str);      // 记录用户输入的宠物姓名和种类

int main(void)
{
	Tree pets;
	char choice;

	InitializeTree(&pets);
	while ((choice = menu()) != 'q')
	{
		switch (choice)
		{
		case 'a': addpet(&pets);		break;
		case 'l': showpets(&pets);		break;
		case 'f': findpet(&pets);		break;
		case 'n': printf("%d pets in club\n", TreeItemCount(&pets));  break;
		case 'd': droppet(&pets);		break; 
		default : puts("Switching error");
		}
	}
	DeleteAll(&pets);
	puts("Bye.");

	return 0;
}

char menu(void)
{
	// 显示菜单响应用户操作
	int ch;

	puts("\nNerfville Pet Club Membership Program");
	puts("Enter the letter corresponding to your choice:");
	puts("a) add a pet        l) show list of pets");
	puts("n) number of pets   f) find pets");
	puts("d) delete a pet     q) quit");

	while ((ch = getchar()) != EOF)
	{
		while (getchar() != '\n')
			continue;
		ch = tolower(ch);
		if (strchr("alrfndq", ch) == NULL)
			puts("Undefined opnion");
		else
			break;
	}
	if (ch == EOF)
		ch = 'q';

	return ch;
}

void Ask_The_Pet(Item * item, char * str)
{
	// 记录用户输入的宠物姓名和种类
	item->kindcount = 0;
	printf("Please enter name of pet you wish to %s:", str);
	s_gets(item->petname, SLEN);
	printf("Please enter kind of pet you wish to %s:", str);
	s_gets(item->petkind[0], SLEN);
	uppercase(item->petname);
	uppercase(item->petkind[0]);
}

void addpet(Tree * pt)
{
	// 执行用户操作添加宠物
	Item temp;

	if (TreeIsFull(pt))
		puts("No room in the club!");
	else
	{
		Ask_The_Pet(&temp, "add");
		AddItem(&temp, pt);
	}
}

void showpets(const Tree * pt)
{
	// 执行用户操作显示宠物列表
	if (TreeIsEmpty(pt))
		puts("No entries!");
	else
		Traverse(pt, printitem);
}

void printitem(Item item)
{
	// 打印二叉树单个节点内的对象的信息
	printf("Pet: %-19s\n", item.petname);
	for(int i = 0; i <= item.kindcount; i++)
		printf("Kind: %-19s\n", item.petkind[i]);
}

void findpet(const Tree * pt)
{
	// 执行用户操作查询宠物
	Item temp;

	if (TreeIsEmpty(pt))
	{
		puts("No entries!");
		return;
	}

	Ask_The_Pet(&temp, "find");
	printf("%s the %s ", temp.petname, temp.petkind);
	if (InTree(&temp, pt))
		printf("is a member.\n");
	else
		printf("is not a member.\n");
}

void droppet(Tree * pt)
{
	// 执行用户操作删除宠物
	Item temp;

	if (TreeIsEmpty(pt))
	{
		puts("No entries!");
		return;
	}

	Ask_The_Pet(&temp, "delete");
	printf("%s the %s ", temp.petname, temp.petkind);

	if (DeleteItem(&temp, pt))
		printf("is dropped from the club.\n");
	else
		printf("is not a member.\n");
}

void uppercase(char * str)
{
	// 将字符串转为大写
	while (*str)
	{
		*str = toupper(*str);
		str++;
	}
}

char * s_gets(char * st, int n)
{
	// 读取一行输入
	char * ret_val;
	char * find;

	ret_val = fgets(st, n, stdin);
	if (ret_val)
	{
		find = strchr(st, '\n');
		if (find)
			*find = '\0';
		else
			while (getchar() != '\n')
				continue;
	}

	return ret_val;
}
