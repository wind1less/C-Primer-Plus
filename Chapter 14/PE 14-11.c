// 编写一个名为transform() 的函数，接受4 个参数：
// 内含double 类型数据的源数组名、内含double 类型数据的目标数组名、
// 一个表示数组元素个数的int 类型参数、函数名（或等价的函数指针）。
// transform() 函数应把指定函数应用于源数组中的每个元素，并把返回值存储在目标数组汇总。
// 例如：
// transform(source, target, 100, sin);
// 该声明会把target[0] 设置为sin(source[0]),等等，一共有100 个元素。
// 在一个程序中调用transform() 4次，以测试该函数。
// 分别使用math.h 函数库中的两个函数以及自定义的两个函数作为参数。

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef double (*fp)(double n);

#define MAX 100

double half(double n);
double quarter(double n);


void transform(double * source, double * target, int n, fp func);
void show_ary(double *, int n);

int main(void)
{
	double source[MAX];
	double target[MAX];
	for (int i = 0; i < MAX; i++)
		source[i] = (float)rand() / 100;
	printf("Source array:\n");
	show_ary(source, MAX);

	transform(source, target, MAX, fabs);
	printf("After fabs():\n");
	show_ary(target, MAX);

	transform(source, target, MAX, sqrt);
	printf("After sqrt():\n");
	show_ary(target, MAX);

	transform(source, target, MAX, half);
	printf("After half():\n");
	show_ary(target, MAX);

	transform(source, target, MAX, quarter);
	printf("After quarter():\n");
	show_ary(target, MAX);
}

void transform(double * source, double * target, int n, fp func)
{
	for (int i = 0; i < n; i++)
	{
		target[i] = func(source[i]);
	}
}

void show_ary(double * ary, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (i && (i % 8 == 0))
			printf("\n");
		printf("%10f  ", ary[i]);
	}
	printf("\n________________________________________________________________________________________________\n");
}

double half(double n)
{
	return n / 2;
}

double quarter(double n)
{
	return n / 4;
}