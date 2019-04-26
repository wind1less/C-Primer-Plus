// 编写一个程序，接受两个int 类型的参数：一个是值；一个是位的位置。
// 如果指定位的位置为1，该函数返回；否则返回0。
// 在一个程序中测试该函数。

#include <stdio.h>
#include <stdlib.h>

int get_value(int *);
int get_pos(int *);
int find_pos(int, int);

const size = CHAR_BIT * sizeof(int);

int main()
{
	int value;
	int pos;

	while (get_value(&value) && get_pos(&pos))
	{
		printf("%d as binary num, pos %d is %d.\n", value, pos, find_pos(value, pos));
	}

	puts("Done.");

	return 0;
}

int get_value(int * n)
{
	printf("Enter a number(q to quit):\n");
	
	return (scanf("%d", n) == 1);
}

int get_pos(int * n)
{

	printf("Enter a pos(0 ~ %d)\n", size - 1);
	while (scanf("%d", n) != 1 || *n < 0 || *n > size)
		printf("Invalid value, try again:\n");

	return 1;
}

int find_pos(int value, int pos)
{
	int find;

	for (int i = 0; i < pos; i++, value >>= 1)
		;
	find = (01 & value);

	return find;
}





