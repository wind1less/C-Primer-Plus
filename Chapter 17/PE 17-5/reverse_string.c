#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

char * s_gets(char * st, int n);

#define SLEN 20

int main(void)
{
	Stack string;	                // 创建栈
	char input[SLEN];
	char * temp;
  
	InitializeStack(&string);       // 初始化栈

	printf("Enter a string (empty line to quie):\n");
	while (s_gets(input, SLEN) != NULL && input[0] != '\0')
	{
        // 检查栈满
		if (StackIsFull(&string))
		{
			fprintf(stderr, "Stack is full!");
			exit(1);
		}
        // 将输入的字符逐字推入栈
		temp = input;
		while (*temp != '\0')
		{
			PushStack(*temp, &string);
			temp++;
		}
        
        // 将栈内字符逐字弹出并打印
		while (!StackIsEmpty(&string))
		{
			PopStack(temp, &string);
			putchar(*temp);
		}
        
		printf("\nEnter next string:\n");
	}
    
    EmptyTheStack(&string);         // 清空栈
    puts("Done.");

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
