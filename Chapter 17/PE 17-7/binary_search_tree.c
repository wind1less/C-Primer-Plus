// 编写一个程序，打开和读取一个文本文件，并统计文件中每个单词出现的次数。
// 用改进的二叉查找树储存单词及其出现的次数。
// 程序在读入文件后，会提供一个有3 个选项的菜单。
// 第1 个选项是列出所有的单词和出现的次数。第2 个选项是让用户输入一个单词，程序报告该单词在文件中出现的次数。第3 个选项是退出。

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tree.h"

bool update_word(char * st, Tree * ptree);		// 将读取到的单词写入二叉树，检测单词是否已存在于二叉树，执行递增项或新加项
void print_item(Item item);						// 打印单个节点内对象的信息

int get_menu(void);								// 显示用户操作菜单，记录用户操作
void eat_line(void);							// 配合scanf() 函数后，清空输入缓冲区
void show_all_words(Tree * ptree);				// 显示二叉树内所有节点的信息
void show_word_count(Tree * ptree);				// 显示二叉树内目标对象的计数

int main(void)
{
	Tree ptree;								// 目标链表二叉树
	FILE * pf;								// 目标文件指针
	char file_name[40] = "book1.txt";		// 目标文件
	int choice;								// 记录菜单选择

	bool in_word = false;					// 标记当前从文件流中读取的字符是否位于单词中
	char word[SLEN];						// 从文件中读取整个单词
	int ch;									// 从文件中逐字读取
	int word_index = 0;						// 单词的索引

	InitializeTree(&ptree);					// 初始化链表

	// 初始化文件指针
	pf = fopen(file_name, "r");
	if (pf == NULL)
	{
		fprintf(stderr, "Can't open %s.\n", file_name);
		exit(1);
	}

	// 从文件中逐单词写入二叉树
	while ((ch = getc(pf)) != EOF)
	{
		while (!isalpha(ch))
		{
			if (in_word)
			{
				word[word_index] = '\0';
				update_word(word, &ptree);
			}
			ch = getc(pf);
			word_index = 0;
			in_word = false;
			if (ch == EOF)
				break;
		}
		in_word = true;
		word[word_index] = tolower(ch);
		word_index++;
	}
	if (in_word)
	{
		word[word_index] = '\0';
		update_word(word, &ptree);
	}

	// 二叉树编写完成，响应用户操作
	while ((choice = get_menu()) != 3)
	{
		switch (choice)
		{  
		case 1: show_all_words(&ptree);			break;
		case 2: show_word_count(&ptree);			break;
		default: fprintf(stderr, "Invaild choice!!!\n");
		}
	}
	
	// 程序完成，执行清理操作
	fclose(pf);
	printf("Tree size: %d", ptree.size);
	DelTree(&ptree);
	printf("\nOver!");

	return 0;
}


int get_menu(void)
{
	// 显示用户操作菜单，记录用户操作
	int choice;
	printf("Operate opnion:\n");
	printf("1) show all word count        2) show assign word count\n");
	printf("3) quit\n");
	scanf("%d", &choice);
	eat_line();

	return choice;
}

void eat_line(void)
{
	// 清空输入缓冲区
	while (getchar() != '\n')
		continue;
}

void show_all_words(Tree * ptree)
{
	// 显示二叉树内所有节点的信息
	Traverse(ptree, print_item);
}

void show_word_count(Tree * ptree)
{
	// 显示二叉树内目标对象的计数
	Node * temp;
	int count = 0;
	Item item;
	char be_find[SLEN];
	printf("Which word do you want to find:\n");
	scanf("%s", be_find);
	eat_line();

	strcpy(item.word, be_find);
	temp = FindItem(item, ptree->root);
	if (temp == NULL)
		printf("No this word.\n");
	else
		printf("%s covers %d times.\n", temp->item.word, temp->item.count);
}

bool update_word(char * st, Tree * ptree)
{

	// 将读取到的单词写入二叉树，检测单词是否已存在于二叉树，执行递增项或新加项
	Item item;

	strcpy(item.word, st);
	item.count = 1;
	if (InTree(item, ptree) == false)
		AddItem(item, ptree);

	return true;
}

void print_item(Item item)
{
	// 打印单个节点内对象的信息
	printf("Word [%15s] Count [%d]\n", item.word, item.count);
}
