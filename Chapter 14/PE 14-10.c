// 编写一个程序，通过一个函数指针数组实现菜单。
// 例如，选择菜单中的a，将激活由该数组第1 个元素指向的函数。

#include <stdio.h>

int func_a();
int func_b();
int func_c();

int main(void)
{
	int order = 0;
	int(*pf[3])() = { func_a, func_b, func_c };
	printf("Select a function ( 0 - 2, overrange to quit ):\n");
	while (scanf("%d", &order) == 1 && order < 3 && order > -1)
	{
		while (getchar() != '\n')
			continue;
		pf[order]();		// 两种通过函数指针调用函数的方式
		//(*pf[order])();
	}
}

int func_a()
{
	printf("This is function A!\n");

	return 1;
}

int func_b()
{
	printf("This is function B!\n");

	return 2;
}

int func_c()
{
	printf("This is function C!\n");

	return 2;
}
