// 假设list.h 使用下面的list 定义：
// typedef strcut list
// {
//     Node * head;        /* 指向list 的开头 */
//     Node * end;         /* 指向list 的末尾 */
// } List;
// 重写list.c 中的函数以适应新的定义，并通过films.c 测试最终的代码

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

void showmovies(Item item);
void eat_line(void);
char * s_gets(char * st, int n);

int main(void)
{
	List movies;
	Item temp;

	// 初始化
	InitializeList(&movies);
	if (ListIsFull())
	{
		fprintf(stderr, "No memeory avaiable! Bye!\n");
		exit(1);
	}

	// 获取用户数据
	puts("Enter the first movie title:");
	while (s_gets(temp.title, TSIZE) != NULL && temp.title[0] != '\0')
	{
		puts("Enter your rating <0-10>:");
		scanf("%d", &temp.rating);
		eat_line();
		if (AddItem(temp, &movies) == false)
		{
			fprintf(stderr, "Problem allocating memory\n");
			break;
		}
		if (ListIsFull())
		{
			puts("The list is now full.");
			break;
		}
		puts("Enter next movie title (empty line to stop):");
	}

	// 回显链表信息
	if(ListIsEmpty(&movies))
		puts("No data entered.");
	else
	{
		puts("Here is the movie list:\n");
		Traverse(&movies, showmovies);
	}
	printf("You entered %d movies.\n", ListItemCount(&movies));

	// 清理链表
	EmptyTheList(&movies);
	printf("Bye!");

	return 0;
}

void showmovies(Item item)
{
	printf("Movies: %-15s    Rating: %-3d\n", item.title, item.rating);
}

void eat_line(void)
{
	while (getchar() != '\n')
		continue;
}

char * s_gets(char * st, int n)
{
	char * ret_val;
	char * find;

	ret_val = fgets(st, n, stdin);
	if (ret_val)
	{
		find = strchr(st, '\n');
		if (find)
			*find = '\0';
		else
			eat_line();
	}

	return ret_val;
}
