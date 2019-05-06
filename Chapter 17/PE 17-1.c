#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TSIZE 45

struct film {
	char title[TSIZE];
	int rating;
	struct film * last;
	struct film * next;
};

char * s_gets(char * st, int n);
void show_list(const struct film * pf);

int main(void)
{
	struct film * head = NULL;
	struct film * prev, *current;
	char input[TSIZE];

	puts("Enter first movie title:");
	while (s_gets(input, TSIZE) != NULL && input[0] != '\0')
	{
		current = (struct film *)malloc(sizeof(struct film));
		if (head == NULL)
		{
			current->last = NULL;
			head = current;
		}
		else
		{
			prev->next = current;
			current->last = prev;
		}
		current->next = NULL;
		strcpy(current->title, input);
		puts("Enter your rating <0-10>:");
		scanf("%d", &current->rating);
		while (getchar() != '\n')
			continue;
		puts("Enter next movie title(empty line to stop):");
		prev = current;
	}

	if (head == NULL)
		printf("No data entered.");
	else
	{
		printf("Here is the movie ahead list:\n");
		current = head;
		show_list(current);
    
		//while (current != NULL)
		//{
		//	printf("Movie : %-17s Rating : %3d\n", current->title, current->rating);
		//	prev = current;
		//	current = current->next;
		//}

		/* -----------下面是使用双向遍历链表的方法---------------------

		printf("Here is the movie back list:\n");
		while (prev != NULL)
		{
			printf("Movie : %-17s Rating : %3d\n", prev->title, prev->rating);
			prev = prev->last;
		}

		 ------------------------------------------------------------*/
     
	}

	current = head;
	while (current != NULL)
	{
		prev = current->next;
		free(current);
		current = prev;
	}
	printf("Bye!\n");

	return 0;
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
			while (getchar() != '\n')
				continue;
	}

	return ret_val;
}


// 使用递归方式逆序遍历链表
void show_list(const struct film * pf)
{
	if (pf == NULL)
		return;
	else
	{
		show_list(pf->next);
		printf("Movie : %-17s Rating : %3d\n", pf->title, pf->rating);
	}
}
